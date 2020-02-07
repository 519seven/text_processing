
readonly PROGNAME=$(basename $0)
readonly PROGDIR=$(readlink -m $(dirname $0))
readonly ARGS="$@"

cmdline() {
    local arg=$1
    for arg; do
        local delim=""
        case "$arg" in
            #translate --gnu-long-options to -g (short options)
            --debug)                args="${args}-d ";;
            --help)                 args="${args}-h ";;
            --repo-name)            args="${args}-r ";;
            --group-name)           args="${args}-g ";;
            --dry-run)              args="${args}-n ";;
            --test)                 args="${args}-t ";;
            --verbose)              args="${args}-v ";;
            #pass through anything else
            *) [[ "${arg:0:1}" == "-" ]] || delim="\""
                args="${args}${delim}${arg}${delim} ";;
        esac
    done

    #Reset the positional parameters to the short options
    eval set -- $args

    while getopts "dhr:g:t:c:" OPTION; do
         case $OPTION in
         d)
            # debug
            readonly VERBOSE=1
            ;;
         h)
            # help
            usage
            exit 0
            ;;
         r)
            # package repo name
            readonly REPO_NAME=$OPTARG
            ;;
         g)
            # package group name
            readonly GROUP_NAME=$OPTARG
            ;;
         n)
            # pretend (dry-run)
            readonly DRY_RUN=$OPTARG
            ;;
         t)
            # tests
            readonly REPO_NAME=$OPTARG
            verbose VINFO "Running tests"
            ;;
         v)
            # verbose logging
            readonly _V=$OPTARG
            ;;
        esac
    done

    return 0
}

log() {
    if [[ $_V -eq 1 ]]; then
      echo "$@"
    fi
}

get_pkg_list() {
    local repo_name = $1 ;
    local group_name = $2 ;
    log "Getting package list from group" $repo_name "and group name" $group_name
    pkg_list=$(yum --disablerepo=* --enablerepo=ia-latest group info $1);
    return 0
}

print_list() {
    local pkg_list = $1 ;
    for i in $pkg_list; do
      if [ "$i" = +* ]; then
        echo $i;
      fi
    done
}

usage() {
    printf "$0 <repo_name> <group_name>\n"
    printf "Ex: $0 \"ia-latest\" \"IA\"\n"
    return 0
}

main() {
    cmdline $1
    return 0
}

main $ARGS
exit 0