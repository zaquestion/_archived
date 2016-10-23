package main

import (
	"encoding/json"
	"net/http"

	"github.com/codegangsta/negroni"
)

func main() {
	mux := http.NewServeMux()
	mux.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		buf := new(bytes.Buffer)
		buf.ReadFrom(r.Body)

		fmt.Println(buf.String())
	})

	n := negroni.Classic()
	n.UseHandler(mux)
	n.Run(":3001")
}
