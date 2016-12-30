NoteHub
--

NoteHub is a service for storing your notes on github. We'll automagically date and organize your notes for you. Then you can use your text search tool of choice to find them.

Currently the server needs to be started with an underlying ssh agent to be usable. Alternately use an ssh key with no passphrase. NoteHub is bring your open repo so you're free to set that up however you like. Just configure the path to it in the notehub config.

```
go run cmd/main.go <config>
```

Intention
--

Mostly built for spite based off of a project that could have been simpler :P http://github.com/adamryman/twonote

