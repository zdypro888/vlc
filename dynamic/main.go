package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
	"regexp"
)

func main() {
	names := make(map[string]int)
	var libvlcgoreg = regexp.MustCompile(`C\.libvlc_([a-zA-Z0-9_]*?)\(`)
	filepath.Walk("../", func(path string, info os.FileInfo, err error) error {
		if err == nil && !info.IsDir() && filepath.Ext(path) == ".go" {
			log.Printf("文件: %s", path)
			filedata, err := ioutil.ReadFile(path)
			if err != nil {
				return err
			}
			results := libvlcgoreg.FindAllStringSubmatch(string(filedata), -1)
			for _, result := range results {
				name := fmt.Sprintf("libvlc_%s", result[1])
				names[name] = 1
			}
		}
		return nil
	})
	log.Println(names)
	var cfunctions string
	var libvlcreg = regexp.MustCompile(`(?m)LIBVLC_API[\s]*?(\w+?)[\s]*?libvlc_(.*?)\((.*?)\);`)
	filepath.Walk("../", func(path string, info os.FileInfo, err error) error {
		if err == nil && !info.IsDir() && filepath.Ext(path) == ".h" {
			log.Printf("文件: %s", path)
			filedata, err := ioutil.ReadFile(path)
			if err != nil {
				return err
			}
			results := libvlcreg.FindAllStringSubmatch(string(filedata), -1)
			for _, result := range results {
				name := fmt.Sprintf("typedef %s (*p_libvlc_%s)(%s);\n", result[1], result[2], result[3])
				cfunctions += name
			}
		}
		return nil
	})
	log.Println(cfunctions)

}
