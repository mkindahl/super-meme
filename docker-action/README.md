Testing if it is possible to pass back files to the calling VM,
which seems to be possible.

The environment is set inside the entrypoint script, which is obvious.

Running docker maps the following directories, with the current
working directory in bold:

| Virtual Machine Directory                       | Container Directory     |
| ----------------------------------------------- | ----------------------- |
| `/var/run/docker.sock`                          | `/var/run/docker.sock`  |
| `/home/runner/work/_temp/_github_home`          | `/github/home`          |
| `/home/runner/work/_temp/_github_workflow`      | `/github/workflow`      |
| `/home/runner/work/_temp/_runner_file_commands` | `/github/file_commands` |
| **`/home/runner/work/super-meme/super-meme`**   | **`/github/workspace`** |
