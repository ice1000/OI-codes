package kata_test

import (
	. "github.com/onsi/ginkgo"
	. "github.com/onsi/gomega"
	. "codewarrior/kata"
	"math/rand"
	"fmt"
)

// Encoding table holds all the characters for base91 encoding
var enctab = []byte("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!#$%&()*+,./:;<=>?@[]^_`{|}~'")

// Encode returns the base91 encoded string
func encode(d []byte) []byte {
	var n, b uint
	var o []byte

	for i := 0; i < len(d); i++ {
		b |= uint(d[i]) << n
		n += 8
		if n > 13 {
			v := b & 8191
			if v > 88 {
				b >>= 13
				n -= 13
			} else {
				v = b & 16383
				b >>= 14
				n -= 14
			}
			o = append(o, enctab[v%91], enctab[v/91])
		}
	}
	if n > 0 {
		o = append(o, enctab[b%91])
		if n > 7 || b > 90 {
			o = append(o, enctab[b/91])
		}
	}
	return o
}

func r() int64 {
	return int64(rand.Intn(20000))
}

// EncodeToString encodes the given byte array and returns a string
func EncodeToString(d []byte) string {
	return string(Encode(d))
}

// DecodeToString decodes a given byte array are returns a string
func DecodeToString(d []byte) string {
	return string(Decode(d))
}

var _ = Describe("Tests", func() {
	It("should pass example tests", func() {
		Expect(DecodeToString([]byte("fPNKd"))).To(Equal("test"))
		Expect(DecodeToString([]byte(">OwJh>Io0Tv!8PE"))).To(Equal("Hello World!"))
		Expect(EncodeToString([]byte("test"))).To(Equal("fPNKd"))
		Expect(EncodeToString([]byte("Hello World!"))).To(Equal(">OwJh>Io0Tv!8PE"))
	})
	It("should pass random tests", func() {
		for i := 0; i < 200; i++ {
			origin := fmt.Sprintf("%s%s%s%s%s%s%s%s%s%s%s", r(), r(), r(), r(), r(), r(), r(), r(), r(), r(), r())
			encoded := string(encode([]byte(origin)))
			Expect(EncodeToString([]byte(origin))).To(Equal(encoded))
			Expect(DecodeToString([]byte(encoded))).To(Equal(origin))
		}
	})
})
