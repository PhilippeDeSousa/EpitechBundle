if [ "$#" -ne 1 ]; then
    echo "Usage: " $0 " <branch-name>"
    exit
fi

git checkout master && \
    git pull && \
    git checkout $1 && \
    git rebase master && \
    git push && \
    git checkout master && \
    git merge $1 && \
    git push && \
    git checkout $1 && \
    echo && \
    echo "Successfully merged " $1 " onto master" && \
    echo
