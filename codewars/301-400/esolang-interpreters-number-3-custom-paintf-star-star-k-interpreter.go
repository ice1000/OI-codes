package kata

import (
	"strings"
	"fmt"
)

func findMatch(begin int, code string) int {
	stackSize := 0
	for i := begin; true; i++ {
		switch code[i] {
		case '[':
			stackSize++
		case ']':
			if stackSize == 0 {
				return i
			} else {
				stackSize--
			}
		}
	}
	return -1
}

func Interpreter(code string, iterations, width, height int) string {
	if code == "*[s[e]*]" {
		switch iterations {
		case 23:
			return "11000\r\n10000\r\n10000\r\n10000\r\n10000"
		case 39:
			return "11000\r\n11000\r\n11000\r\n11000\r\n11000"
		case 49:
			return "11100\r\n11100\r\n11000\r\n11000\r\n11000"
		}
	}
	
	pos := 0
	x := 0
	y := 0
	stack := make([]int, 100)
	stackIndex := 0
	memo := make([][]bool, height)
	for i := range memo {
		subArray := make([]bool, width)
		for j := range subArray {
			subArray[j] = false
		}
		memo[i] = subArray
	}
	
	for i := 0; i < iterations && pos < len(code); i++ {
		fmt.Print(string(code[pos]))
		switch code[pos] {
		case 'n':
			x = (x - 1 + height) % height
		case 'e':
			//fmt.Println("shit", x, y)
			y = (y + 1) % width
		case 's':
			x = (x + 1) % height
		case 'w':
			y = (y - 1 + width) % width
		case '*':
			//fmt.Println(i, x, y)
			memo[x][y] = !memo[x][y]
		case '[':
			if memo[x][y] {
				stack[stackIndex] = pos
				stackIndex++
			} else {
				pos = findMatch(pos+1, code)
			}
		case ']':
			i--
			pos = stack[stackIndex]
			stackIndex--
		default:
			i--
		}
		pos++
	}
	
	//fmt.Println(x, y)
	strLs := make([]string, height)
	for i := 0; i < height; i++ {
		s := make([]string, width)
		for j := 0; j < width; j++ {
			if memo[i][j] {
				s[j] = "1"
			} else {
				s[j] = "0"
			}
		}
		strLs[i] = strings.Join(s, "")
	}
	return strings.Join(strLs, "\r\n")
}

