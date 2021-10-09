package main

import (
  "bufio"
  "os"
  "strconv"
)

type IO struct {
  scanner *bufio.Scanner
  writer *bufio.Writer
}
func NewIO() IO {
  io := IO{scanner: bufio.NewScanner(os.Stdin), 
    writer: bufio.NewWriter(os.Stdout)}
  io.scanner.Split(bufio.ScanWords)
  return io
}
func toInt(buf []byte) (n int) {
  sgn := false
  for _, v := range buf {
    if v == '-' {
      sgn = true
    } else {
      n = n*10 + int(v-'0')
    }
  }
  if sgn {
    n = -n
  }
  return
}
func (io *IO) NextInt() int {
  io.scanner.Scan()
  return toInt(io.scanner.Bytes())
}
func (io *IO) Write(data ...interface{}) {
  for _, el := range data {
    switch el.(type) {
      case int:
        io.writer.WriteString(strconv.Itoa(el.(int)))
      case string:
        io.writer.WriteString(el.(string))
      case rune:
        io.writer.WriteRune(el.(rune))
    }
  }
}
func (io *IO) Writeln(data ...interface{}) {
  io.Write(data...)
  io.writer.WriteRune('\n')
}
func (io *IO) Flush() {
  io.writer.Flush()
}

func Max(a, b int) int {
  if a>b {
    return a
  } else {
    return b
  }
}

const N int = 100

func main() {
  io := NewIO()

  n := io.NextInt()
  var a [N](int)
  ans := 0
  for i:=0; i<n; i++ {
    a[i] = io.NextInt()
    if i>0 && a[i]!=1 && a[i-1]!=1 {
      goto Bad
    }
    if i>1 && a[i]==2 && a[i-1]==1 && a[i-2]==3 {
      ans--
    }
    if i>0 {
      if Max(a[i],a[i-1])==2 {
        ans += 3
      } else {
        ans += 4
      }
    }
  }

  io.Writeln("Finite")
  io.Writeln(ans)
  io.Flush()
  return

Bad:
  io.Writeln("Infinite")
  io.Flush()
  return
}
