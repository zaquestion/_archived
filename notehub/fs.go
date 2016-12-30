package notehub

import (
	"io/ioutil"
	"log"
	"os"
	"path"
	"time"
)

func GetCurrentDirectory() string {
	year := time.Now().UTC().Format("2006")
	month := time.Now().UTC().Format("01")
	day := time.Now().UTC().Format("02")
	full := path.Join(repo, path.Join(year, path.Join(month, day)))

	return full
}

func CreateNote() string {
	name := time.Now().UTC().Format("15:04:05") + ".md"
	dir := GetCurrentDirectory()
	err := os.MkdirAll(dir, 0740)
	if err != nil {
		log.Println(err)
	}

	full := path.Join(dir, name)

	_, err = os.OpenFile(full, os.O_CREATE, 0640)
	if err != nil {
		log.Println(err)
	}
	return full
}

func PurgeEmptyFiles() error {
	cur_dir := GetCurrentDirectory()

	files, err := ioutil.ReadDir(cur_dir)
	if err != nil {
		return err
	}

	if len(files) == 0 {
		err = os.Remove(cur_dir)
		if err != nil {
			return err
		}
	}

	for _, file := range files {
		if !file.IsDir() && file.Size() == 0 {
			err = os.Remove(path.Join(cur_dir, file.Name()))
			if err != nil {
				return err
			}
		}
	}
	return nil
}
