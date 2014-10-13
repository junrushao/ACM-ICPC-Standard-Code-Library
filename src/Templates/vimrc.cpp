set nu ru nobk cindent si
set mouse=a sw=4 sts=4 ts=4
set hlsearch incsearch
set whichwrap=b,s,<,>,[,]
syntax on

nmap <C-A> ggVG
vmap <C-C> "+y

autocmd BufNewFile *.cpp 0r ~/Templates/cpp.cpp
map<F9> :!g++ % -o %< -Wall -Wconversion -Wextra -g3 <CR>
map<F5> :!./%< <CR>
map<F8> :!./%< < %<.in <CR>

map<F3> :vnew %<.in <CR>
map<F4> :!(gedit % &)<CR>
