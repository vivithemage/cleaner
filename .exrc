if &cp | set nocp | endif
vnoremap <silent>  :call RangeCommentLine()
nnoremap <silent>  :call CommentLine()
onoremap <silent>  :call CommentLine()
vnoremap <silent>  :call RangeUnCommentLine()
nnoremap <silent>  :call UnCommentLine()
onoremap <silent>  :call UnCommentLine()
let s:cpo_save=&cpo
set cpo&vim
nmap gx <Plug>NetrwBrowseX
map tt :NERDTreeToggle
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
map <F3> :w !detex | wc -w
map <silent> <F10> :setlocal spell! spelllang=en_gb
let &cpo=s:cpo_save
unlet s:cpo_save
set paste
set background=dark
set backspace=indent,eol,start
set cindent
set cinkeys=‚Äù0{,0},0#,:‚Äù
set cinoptions=‚Äù>2,{3,}3‚Äù
set cinwords=‚Äùif,,else,do,while,for,switch‚Äù
set expandtab
set history=500
set ignorecase
set incsearch
set laststatus=2
set makeprg=scons
set matchtime=2
set mouse=a
set shiftwidth=2
set shortmess=filnxtToOI
set showcmd
set smarttab
set statusline=%F%m%r%h%w\ [format=%{&ff}]\ [type=%Y]\ [ascii=%03.3b]\ [position=%04l,%04v][%p%%]\ [length=%L]
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc
set noswapfile
set tabstop=2
set wildmenu
set winminheight=0
set nowritebackup
" vim: set ft=vim :
