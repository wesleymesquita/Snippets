package main

import (
	"bufio"
	"fmt"
	"log"
	"math/rand"
	"os"
	"os/exec"
)

const (
	letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
)

func main() {
	text := editTextInVim()
	fmt.Println("Text == : ", text)
}
func editTextInVim() string {
	tmpFile := generateRandomFilename(".txt")
	cmd := exec.Command("vim", tmpFile)
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	err := cmd.Run()
	if err != nil {
		log.Println("Could not execute vim: ", err)
		return ""
	}
	file, err := os.Open(tmpFile)
	if err != nil {
		log.Println("Error while retrieving text: ", err)
		return ""
	}
	scanner := bufio.NewScanner(file)
	scanner.Scan()
	text := scanner.Text()
	cmdRm := exec.Command("rm", tmpFile)
	cmdRm.Stdin = os.Stdin
	cmdRm.Stdout = os.Stdout
	err = cmdRm.Run()
	if err != nil {
		log.Println("Could not delete temp file")
	}
	return text
}

func generateRandomFilename(ext string) string {

	fileNameSize := 64
	nameBytes := make([]byte, fileNameSize)

	for i := 0; i < fileNameSize; i++ {
		nameBytes[i] = byte(letters[rand.Intn(len(letters))])
	}

	fileName := string(nameBytes)
	fileName += "." + ext
	return fileName
}
