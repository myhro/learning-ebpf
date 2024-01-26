package main

import (
	"log"
	"time"

	"github.com/cilium/ebpf/link"
)

func main() {
	var objs helloObjects

	err := loadHelloObjects(&objs, nil)
	if err != nil {
		log.Fatalf("loadHelloObjects: %v", err)
	}
	defer objs.Close()

	tp, err := link.Tracepoint("syscalls", "sys_enter_execve", objs.Hello, nil)
	if err != nil {
		log.Fatalf("link.Tracepoint: %v", err)
	}
	defer tp.Close()

	for {
		time.Sleep(time.Second)
	}
}
