package main

import (
	"bytes"
	"fmt"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
	"regexp"
	"strings"

	"modernc.org/cc/v3"
)

var parserTestBuiltin = `
#define __DI__
#define __FUNCTION__ __func__
#define __HI__
#define __PRETTY_FUNCTION__ __func__
#define __QI__
#define __SI__
#define __builtin_add_overflow(...) 0
#define __builtin_constant_p(x) (__builtin_constant_p_impl(0, x))
#define __builtin_expect(exp, c) (exp)
#define __builtin_mul_overflow(...) 0
#define __builtin_offsetof(type, member) ((__SIZE_TYPE__)&(((type*)0)->member))
#define __builtin_sub_overflow(...) 0
#define __builtin_va_arg(ap, type) ((type)__builtin_va_arg_impl(ap))
#define __builtin_va_end(ap)
#define __builtin_va_start(ap, v)
#define __declspec(...)
#define __extension__
#define __read_only__ 0
#define __signed signed
#define __sync_synchronize(...)
#define __word__
#define __write_only__ 0
#define asm __asm__

#ifndef __GNUC__
#define __attribute__(x)
#endif

#ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#endif

#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ size_t;
#endif

#ifdef __WCHAR_TYPE__
typedef __WCHAR_TYPE__ wchar_t;
#endif

typedef void * __builtin_va_list;

#if __SIZEOF_POINTER__ == 8
#else
typedef long double __float128;
#endif

#ifdef __UINT16_TYPE__
__UINT16_TYPE__ __builtin_bswap16 (__UINT16_TYPE__ x);
#endif

#ifdef __UINT32_TYPE__
__UINT32_TYPE__ __builtin_bswap32 (__UINT32_TYPE__ x);
#endif

#ifdef __UINT64_TYPE__
__UINT64_TYPE__ __builtin_bswap64 (__UINT64_TYPE__ x);
#endif

#ifdef __SIZEOF_INT128__
typedef __INT64_TYPE__ __int128_t[2];	//TODO
typedef __UINT64_TYPE__ __uint128_t[2];	//TODO
#endif

#if defined(__MINGW32__) || defined(__MINGW64__)
int gnu_printf(const char *format, ...);
int gnu_scanf(const char *format, ...);
int ms_scanf(const char *format, ...);
int ms_printf(const char *format, ...);
#endif

typedef struct { char real, imag; } __COMPLEX_CHAR_TYPE__;
typedef struct { double real, imag; } __COMPLEX_DOUBLE_TYPE__;
typedef struct { float real, imag; } __COMPLEX_FLOAT_TYPE__;
typedef struct { int real, imag; } __COMPLEX_INT_TYPE__;
typedef struct { long double real, imag; } __COMPLEX_LONG_DOUBLE_TYPE__;
typedef struct { long real, imag; } __COMPLEX_LONG_TYPE__;
typedef struct { long long real, imag; } __COMPLEX_LONG_LONG_TYPE__;
typedef struct { long long unsigned real, imag; } __COMPLEX_LONG_LONG_UNSIGNED_TYPE__;
typedef struct { long unsigned real, imag; } __COMPLEX_LONG_UNSIGNED_TYPE__;
typedef struct { short real, imag; } __COMPLEX_SHORT_TYPE__;
typedef struct { unsigned real, imag; } __COMPLEX_UNSIGNED_TYPE__;
typedef struct { unsigned short real, imag; } __COMPLEX_SHORT_UNSIGNED_TYPE__;

int __builtin_clzll (unsigned long long);
int __builtin_constant_p_impl(int, ...);
int __printf__ ( const char * format, ... );
int __scanf__ ( const char *format, ... );
void *__builtin_alloca (size_t);
void *__builtin_extract_return_addr (void *addr);
void *__builtin_frame_address (unsigned int level);
void *__builtin_malloc(size_t);
void *__builtin_stack_save(void);
void *__builtin_va_arg_impl(void* ap);

#define __INTMAX_TYPE__ long
#define __UINTMAX_TYPE__ unsigned long

#define TARGET_CPU_X86_64 1
#define TARGET_OS_UNIX 1

#define __x86_64__ 1

#define int_least8_t char
#define int_least16_t short
#define int_least32_t long
#define int_least64_t long long

#define uint_least8_t char
#define uint_least16_t short
#define uint_least32_t long
#define uint_least64_t long long

#define int_fast8_t char
#define int_fast16_t short
#define int_fast32_t long
#define int_fast64_t long long

#define uint_fast8_t char
#define uint_fast16_t short
#define uint_fast32_t long
#define uint_fast64_t long long

#define uint8_t char
#define uint16_t short
#define uint32_t long
#define uint64_t long long
`

func writeType(writer *bytes.Buffer, cct cc.Type) {
	if cct.Kind() == cc.Ptr {
		elem := cct.Elem()
		if elem.Kind() == cc.Function {
			writer.WriteString(cct.String())
			writer.WriteString(" ")
		} else {
			writeType(writer, elem)
			writer.WriteString("* ")
		}
	} else {
		writer.WriteString(cct.String())
		writer.WriteString(" ")
	}
}

func ccParser() {
	cfg := &cc.Config{PreprocessOnly: false}
	cfg.ABI, _ = cc.NewABIFromEnv()
	tran, err := cc.Translate(cfg,
		[]string{"/Users/zdypro/go/src/github.com/zdypro888/vlc/", "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/12.0.5/include/", "/Library/Developer/CommandLineTools/SDKs/MacOSX11.3.sdk/usr/include/"},
		[]string{"/Users/zdypro/go/src/github.com/zdypro888/vlc/", "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/clang/12.0.5/include/", "/Library/Developer/CommandLineTools/SDKs/MacOSX11.3.sdk/usr/include/"},
		[]cc.Source{{Name: "pre.h", Value: parserTestBuiltin}, {Name: "/Users/zdypro/go/src/github.com/zdypro888/vlc/vlc/vlc.h", DoNotCache: true}})
	if err != nil {
		log.Println(err)
	} else {
		headerWriter := bytes.NewBuffer(nil)
		sourceWriter := bytes.NewBuffer(nil)
		sourceExecWriter := bytes.NewBuffer(nil)
		for key, nodes := range tran.Scope {
			if strings.HasPrefix(key.String(), "libvlc_") {
				for _, node := range nodes {
					switch value := node.(type) {
					case *cc.Enumerator:
						// log.Println(value)
					case *cc.EnumSpecifier:
					case *cc.StructOrUnionSpecifier:
					case *cc.Declarator:
						valueType := value.Type()
						if valueType.Kind() == cc.Function {
							sourceWriter.WriteString("typedef ")
							sourceExecWriter.WriteString("p_")
							sourceExecWriter.WriteString(key.String())
							sourceExecWriter.WriteString(" _")
							sourceExecWriter.WriteString(key.String())
							sourceExecWriter.WriteString(";\n")

							writeType(headerWriter, valueType.Result())
							writeType(sourceWriter, valueType.Result())
							writeType(sourceExecWriter, valueType.Result())

							headerWriter.WriteString("dynamic_")
							sourceWriter.WriteString(" (*p_")
							sourceExecWriter.WriteString("dynamic_")

							headerWriter.WriteString(key.String())
							sourceWriter.WriteString(key.String())
							sourceExecWriter.WriteString(key.String())

							headerWriter.WriteString("(")
							sourceWriter.WriteString(")(")
							sourceExecWriter.WriteString("(")

							pars := valueType.Parameters()
							for i, par := range pars {
								writeType(headerWriter, par.Type())
								writeType(sourceWriter, par.Type())
								writeType(sourceExecWriter, par.Type())
								headerWriter.WriteString(par.Name().String())
								sourceExecWriter.WriteString(par.Name().String())
								if i < len(pars)-1 {
									headerWriter.WriteString(", ")
									sourceWriter.WriteString(", ")
									sourceExecWriter.WriteString(", ")
								}
							}
							headerWriter.WriteString(");\n")
							sourceWriter.WriteString(");\n")
							sourceExecWriter.WriteString(") {\n")
							sourceExecWriter.WriteString("\t return ")
							sourceExecWriter.WriteString(" _")
							sourceExecWriter.WriteString(key.String())
							sourceExecWriter.WriteString("(")
							for i, par := range pars {
								sourceExecWriter.WriteString(par.Name().String())
								if i < len(pars)-1 {
									sourceExecWriter.WriteString(", ")
								}
							}
							sourceExecWriter.WriteString(");\n")
							sourceExecWriter.WriteString("}\n")
						}
					default:
						log.Printf("%v", node)
					}
				}
			}
		}
		log.Print(sourceExecWriter.String())
	}
}

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
	filepath.Walk("../", func(path string, info os.FileInfo, err error) error {
		if err == nil && !info.IsDir() && filepath.Ext(path) == ".go" {
			log.Printf("文件: %s", path)
			filedata, err := ioutil.ReadFile(path)
			if err != nil {
				return err
			}
			filesource := string(filedata)
			for name := range names {
				filesource = strings.ReplaceAll(filesource, fmt.Sprintf("C.%s", name), fmt.Sprintf("C.dynamic_%s", name))
			}
			ioutil.WriteFile(path, []byte(filesource), 0644)
		}
		return nil
	})
	log.Println(names)
}
