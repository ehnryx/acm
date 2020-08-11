package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

var reader = bufio.NewReader(os.Stdin)
var writer = bufio.NewWriter(os.Stdout)

func print(a ...interface{}) { fmt.Fprint(writer, a...) }
func scan(a ...interface{})  { fmt.Fscan(reader, a...) }



func main() {
	// code GOes here

	

	writer.Flush()
	return
}
