package notehub

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"
)

var (
	repo   string
	errors chan error
)

func Run() {
	if len(os.Args) < 2 {
		log.Fatal("Please provide the path to the config")
	}
	f, err := os.OpenFile(os.Args[1], os.O_RDONLY, 0)
	if err != nil {
		log.Fatal(err)
	}
	data, err := ioutil.ReadAll(f)
	if err != nil {
		log.Fatal(err)
	}
	var config map[string]interface{}
	err = json.Unmarshal(data, &config)
	if err != nil {
		log.Println(string(data))
		log.Fatal(err)
	}

	repo = config["repo_path"].(string)
	if err != nil {
		log.Fatal(err)
	}

	if _, err := os.Stat(repo); os.IsNotExist(err) {
		log.Fatal("No such file or directory:", repo)
	}

	go handleErrors(errors)

	http.HandleFunc("/create", createNote)
	http.HandleFunc("/search", searchNotes)
	http.HandleFunc("/path", getPath)
	http.HandleFunc("/sync", syncNotes)
	http.ListenAndServe(":8080", nil)
}

func handleErrors(errors <-chan error) {
	for err := range errors {
		log.Println(err)
	}
}

func createNote(w http.ResponseWriter, r *http.Request) {
	// create directory for the date
	// Increments index for note
	note := CreateNote()
	log.Println(note)
	fmt.Fprintln(w, note)
}

func searchNotes(w http.ResponseWriter, r *http.Request) {
	// TODO
	// Fuzzy search
	// return list of files
	log.Println("TODO Searching...")
}

func syncNotes(w http.ResponseWriter, r *http.Request) {
	go func() {
		errors <- Sync()
	}()
	w.WriteHeader(200)
}

func getPath(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintln(w, GetCurrentDirectory())
}
