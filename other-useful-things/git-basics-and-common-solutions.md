---
description: >-
  Little helper for git related things, no claim to completeness! Google/Chatgpt
  are probably your better helpers! In general: DON'T BE AFRAID, THERE'S NEARLY
  ALWAYS A WAY OUT!
---

# Git basics & common solutions

## Standard Git workflow for commits to this repo

There are many ways to work with git and there are advantages and disadvantages to every one of them. Two general things to consider are:

* How well do you know how to work with git?
* How intrusive will your changes be to the work of others?

If you aren't confident in operating with git or are expecting the changes to be rather intrusive, please work on a `fork`  (if you don't yet have direct commit rights) or a `branch`  (if you have maintainer rights to the repo). On the `main` branch, ideally only experts should be pushing directly.&#x20;

### Working on a `fork`

Create a `fork` of the repo in your own github user environment. Then follow the instruction below to setup a proper local structure:

```bash
git clone git@github.com:eic/epic-lfhcal-tbana.git $WHATEVERYOURDIRNAMESHOULDBE
cd $WHATEVERYOURDIRNAMESHOULDBE
git remote -v
#return 
origin	git@github.com:eic/epic-lfhcal-tbana.git (fetch)
origin	git@github.com:eic/epic-lfhcal-tbana.git (push)
# this means you current have setup one remote (origin), now add yours
git remote add $YOURFORK git@github.com:$YOURUSERNAME/epic-lfhcal-tbana.git
## now git remote -v shoulf give you another 2 lines with your username and location on git
# now you should always pull from origin (default will always pull from origin)
git pull origin main
## however push to your fork
git push $YOURFORK main
## you can also setup that by default you would always push to $YOURFORK
git config local remote.pushDefault $YOURFORK
```

Afterwards continue with the [getting started setup](../tb-analysis-basics/). If you made changes and want to push something and have it merged back into the central repository. Go to your fork `Contribute` -> `Create Pull Request`  and the the corresponding dialog opens. Make sure you write a short summary of what you changed and make the request. If we don't react within a few days, send the link to the TB channel and ask for a review of the changes, if its urgent you can always reach out to [Friederike Bock](https://app.gitbook.com/u/5a3295149734bf002fa4a00e "mention").

### Working on a `branch`&#x20;

The initial setup works exactly as described for [getting started setup](../tb-analysis-basics/), then I suggest you read through the [git documentation for branches](https://git-scm.com/book/en/v2/Git-Branching-Basic-Branching-and-Merging) (simply because its useful). In order to push to the repo we'll need to have given you rights & you'll need to be a member of the ["eic organization"](https://github.com/eic). This requires an e-mail to [eic-software-l-request@lists.bnl.gov](mailto:eic-software-l-request@lists.bnl.gov) and your github-profile to contain your **full name** and **current institution**. Afterwards, we can add you to the [github-lfhcal team](https://github.com/orgs/eic/teams/epic-lfhcal) which grants the permissions to this repo.&#x20;

Now lets be real, when you start working please do the following first:

```bash
## check where you are:
git status
## if you are on main, create a branch
git checkout -b $USEFULBRANCHNAME
## if you already have a branch, but for whatever reason aren't on it do
git checkout $USEFULBRANCHNAME
```

Then you work and do you changes, but before you push them upwards don't forget to pull the changes in the remote branches (in particular `main`) and rebase your branch.&#x20;

```bash
## commit your changes
git add $FILENAMES
git commit -m "REASONABLE_COMMIT_MESSAGE"
git fetch
git pull --rebase
git checkout main
git pull --rebase
git checkout $YOURBRANCHNAME
git rebase main
##deal with potential conflicts
git push origin $YOURBRANCHNAME
```

Afterwards you go on the github page and create a pull request, similar to if you'd be working on a `fork` .

### Working on `main`&#x20;

Ideally you leave this to experts. Please ask [Friederike Bock](https://app.gitbook.com/u/5a3295149734bf002fa4a00e "mention")if its ok for you to work here.

## What to do if a merge conflict happens?

Ask yourself a few questions:

*   How far was I behind the branch/repo I want to merge into?

    * If the answer is **really far** it might be worth creating a patch from your commits and applying them to the branch you want to merge in... that might be the quickest solution.
    * If the answer is **close** have a look at the files which have a merge conflict. These should be called out in the messages from the rebase command, i.e.:

    <figure><img src="../.gitbook/assets/Screenshot at 2026-03-27 21-32-43.png" alt=""><figcaption></figcaption></figure>

    * In those cases open the offending files and search for `"<<<<<<<"` , that should bring you to the places where the `HEAD` and your commit differ. The pattern should look something like this

    ```
    <<<<<<< HEAD
    your changes (current branch)
    =======
    incoming changes (other branch)
    >>>>>>> branch-name    
    ```

    * in order to resolve it edit every occurrence of this pattern such that it makes sense and ideally contains the best solution (i.e. not just yours ;) ). Afterwards remover the additional lines starting with "<<<", "===" & ">>>" and do a `git add $FILENAME` , once you edited all files in the conflict messages above do `git rebase --continue` , if the changes can't be trivially resolved or you run into multiple conflicts with successive commits during the rebase consider aborting the rebase and go back to creating a patch.

## How to create & apply a patch?

Patches are a useful way to get out of a bind in some cases and they can be send via email if need be to other people to just check something real quick.&#x20;

```bash
## create a patch with your last commit:
git format-patch HEAD~1
## this should have created a file name 0001-$COMMITMESSAGE.patch
## check whether the patch would break something on a different branch
git checkout $WHATEVERBRANCH
git apply --check 0001-$COMMITMESSAGE.patch
## if nothing appears the patch should work
## applying the patch
git am 0001-$COMMITMESSAGE.patch
```
