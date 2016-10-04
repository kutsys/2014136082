GNU nano 2.5.3        파일 : /home/seungeun/.bashrc

 
# ~/.bashrc: executed by bash(1) for non-login shells.
// ~/.bashrc : 비로그인 쉘을 위해 bash(1)에 의해 실행된다.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
// /usr/share/doc/bash/examples/startup-files를 봐라.(bash-doc 패키지 안에 있는)
# for examples
// 예를 들어
# If not running interactively, don't do anything
// 만약 상호작용으로 실행되지 않는다면, 아무것도 하지 마라.
case $- in 
    *i*) ;;
      *) return;;
esac

 
# don't put duplicate lines or lines starting with space in the history.
// 히스토리 안에 중복된 라인 또는 시작지점에 빈공간을 넣지 마라.
# See bash(1) for more options
// 더 많은 옵션을 보기 위해 bash(1)을 봐라.
HISTCONTROL=ignoreboth

 
# append to the history file, don't overwrite it
// 히스토리 파일을 추가해라, 그것을 덮어쓰지 마라.
shopt -s histappend

 
# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
// 히스토리 길이 설정을 위해 bash(1)의 HISTSIZE와 HISTFILESIZE를 봐라.
HISTSIZE=1000
HISTFILESIZE=2000

 
# check the window size after each command and, if necessary,
// 각각의 명령어 이후 윈도우 사이즈를 체크해라. 만약 필요하다면
# update the values of LINES and COLUMNS.
// 행과 열의 값을 업데이트해라.
shopt -s checkwinsize

 
# If set, the pattern "**" used in a pathname expansion context will
// 설정했다면, 경로이름 확장 문맥에 사용된 "**" 패턴은
# match all files and zero or more directories and subdirectories.
// 모든 파일과 0 또는 많은 디렉토리와 서브디렉토리와 비교할 것이다.
#shopt -s globstar

 
# make less more friendly for non-text input files, see lesspipe(1)
// less를 비 텍스트 입력 파일에 대해 더 친근하게 만들어라. lesspile(1)을 봐라
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

 
# set variable identifying the chroot you work in (used in the prompt below)
// 너가 작업하는 chroot를 식별하는 변수를 설정해라.(사용중인 프롬프트 밑에서)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

 
# set a fancy prompt (non-color, unless we know we "want" color)
// 화려한 프롬프트를 설정해라.(색깔은 없음, 너가 색을 "원한다"를 알고 있지 않다면)
case "$TERM" in // $TERM 이후에 색이 들어간 프롬프트로 함
    xterm-color) color_prompt=yes;;
esac

 
# uncomment for a colored prompt, if the terminal has the capability; turned
// 만약 터미널이 사용 가능하다면, 색깔이 있는 프롬프트에 대해 주석을 달지 마라.
# off by default to not distract the user: the focus in a terminal window
// 사용자에게 혼란을 주지 않게 하기 위해 디폴트를 해제해라. : 터미널창에서의 포커스는
# should be on the output of commands, not on the prompt
// 프롬프트가 아닌 명령의 결과물에 있어야만 한다.
#force_color_prompt=yes

 
if [ -n "$force_color_prompt" ]; then // 
 
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then

 
    # We have color support; assume it's compliant with Ecma-48
    // 우리는 색상 지원을 한다; 그것이 Ecma-48와 순응한다고 가정하자.
    # (ISO/IEC-6429). (Lack of such support is extremely rare, and such
    // (ISO/IEC-6429). (그러한 지원의 부족은 극도로 드물고 그러한)
    # a case would tend to support setf rather than setaf.)
    // 경우는 setaf보다 오히려 setf를 지원하는 경향이 있다.
    color_prompt=yes
    else
    color_prompt=
    fi
fi

 
if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi

 
unset color_prompt force_color_prompt

 
# If this is an xterm set the title to user@host:dir
// 만약 이것이 xterm일 경우, 제목을 user@host:dir로 설정해라.
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

 
# enable color support of ls and also add handy aliases
// ls의 색깔 지원을 가능하게 하고 또한 간단한 명령어를 추가해라.
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"

    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'
    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto' 
fi

 
# some more ls aliases
// 조금 더 많은 명령어들
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

 
# Add an "alert" alias for long running commands.  Use like so:
// 오랫동안 실행되는 명령어들을 위해 "alter"를 추가한다. 다음과 같이 사용한다.
#   sleep 10; alert

 
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'

 
# Alias definitions.
// 명렁어 정의
# You may want to put all your additions into a separate file like
// 너는 ~/.bash_aliases와 같은 분리된 파일에 모든 너의 추가사항을 넣고 싶어할 지 모른다. 
# ~/.bash_aliases, instead of adding them here directly.
// 여기에 직접 추가하는것 대신에
# See /usr/share/doc/bash-doc/examples in the bash-doc package.
// bash-doc패키지에 있는 /usr/share/doc/bash-doc/examples를 봐라.
if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

 
# enable programmable completion features (you don't need to enable
// 사용가능하고 프로그래밍하는 특징 (너는 필요하지 않을것이다 사용가능한 이것들을)
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
// 만약 그것이 이미 in /etc/bash.bashrc와 /etc/profile에서 사용 가능 하다면)
# sources /etc/bash.bashrc).

 
if ! shopt -oq posix; then
  if [ -f /usr/share/bash-completion/bash_completion ]; then
    . /usr/share/bash-completion/bash_completion

  elif [ -f /etc/bash_completion ]; then
    . /etc/bash_completion
   fi
 
fi

