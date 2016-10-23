package main

import (
        "bytes"
        "encoding/json"
        "fmt"
        "math"
        "net/http"
        "sort"

        "github.com/codegangsta/negroni"
)

type Location struct {
        Cid string `json:"user"`
        Lat string `json:"lat"`
        Lon string `json:"lon"`
}

type User struct {
        Cid    string
        Asks   int64
        Trades int64
        Gives  int64
        Rating int64
}

type UserInfo struct {
        Cid    string
        Dist   float64
        Asks   int64
        Trades int64
        Gives  int64
        Rating int64
}

type ByDist []UserInfo

func (a ByDist) Len() int      { return len(a) }
func (a ByDist) Swap(i, j int) { a[i], a[j] = a[j], a[i] }
func (a ByDist) Less(i, j int) { return a[i].Dist < a[j].Dist }

var (
        locations = make(map[string]Location)
)

func main() {
        mux := http.NewServeMux()
        mux.HandleFunc("/", func(w http.ResponseWriter, req *http.Request) {
                buf := new(bytes.Buffer)
                buf.ReadFrom(req.Body)
                //fmt.Println(buf.String())

                var loc Location

                err := json.Unmarshal(buf.Bytes(), &loc)
                if err != nil {
                        fmt.Fprint(w, err)
                        return
                }

                fmt.Fprint(w, loc.cid)
                locations[loc.cid] = loc 
                fmt.Println(len(locations))
        })

        n := negroni.Classic()
        n.UseHandler(mux)
        n.Run(":3000")
}

func prepareNotification(l1 Location, locs map[string]Location) []UserInfo {
        users := make([]UserInfo)

        for k, v := range locs {
                var usr UserInfo
        }

        return sort.Sort(ByDist(users))

}

func getDistanceFromLatLongInKm(lat1 float64, lon1 float64, lat2 float64, lon2 float64) float64 {
	R := 6371.0
	dLat := deg2rad(lat2 - lat1)
	dLon := deg2rad(lon2 - lon1)

	a := math.Sin(dLat/2) * math.Sin(dLat/2) + math.Cos(deg2rad(lat1)) * math.Cos(deg2rad(lat2)) * math.Sin(dLon/2) * math.Sin(dLon/2)

	c := 2 * math.Atan2(math.Sqrt(a), math.Sqrt(1-a))
	d := R * c
	return d
}

func deg2rad(deg float64) float64 {
	return deg * (math.Pi / 180)
}
