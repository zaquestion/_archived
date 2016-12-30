let notehub_server="localhost:8080"

function! Api(cmd)
	return system(printf("curl ".g:notehub_server."/%s 2>/dev/null", a:cmd))
endfunction

" Start plugin
augroup _notehub_init
autocmd!
autocmd BufReadPost *.md call Api("sync")
autocmd BufWritePost *.md call Api("sync")
augroup END

command! NoteN call NewNote()
command! NoteW call WriteNote()

function! NewNote()
	let note = Api("create")
	execute ":e ".note
endfunction

function! WriteNote()
	let note = Api("create")
	execute ":w! ".note
endfunction
