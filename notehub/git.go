package notehub

import (
	"log"
	"os/exec"
	"time"
)

var (
	gitbin string
)

func init() {
	var err error
	gitbin, err = exec.LookPath("git")
	if err != nil {
		log.Fatal(err)
	}
}

func commit() error {
	cmd := exec.Command(gitbin, "add", "*.md")
	cmd.Dir = repo
	if err := cmd.Run(); err != nil {
		return err
	}
	cmd2 := exec.Command(gitbin, "commit", "-am", time.Now().UTC().Format("2006-01-02 15:04:05"))
	cmd2.Dir = repo
	if err := cmd2.Run(); err != nil {
		return err
	}

	return nil
}

func push() error {
	cmd := exec.Command(gitbin, "push", "origin", "master")
	cmd.Dir = repo
	if err := cmd.Run(); err != nil {
		return err
	}

	return nil
}

func pull() error {
	cmd := exec.Command(gitbin, "pull", "origin", "master")
	cmd.Dir = repo
	if err := cmd.Run(); err != nil {
		return err
	}

	return nil
}

func Sync() error {
	err := PurgeEmptyFiles()
	if err != nil {
		return err
	}
	err = commit()
	if err != nil {
		return err
	}
	err = pull()
	if err != nil {
		return err
	}
	err = push()
	if err != nil {
		return err
	}
	return nil
}
