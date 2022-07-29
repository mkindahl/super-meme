# Experiments with Docker GitHub Actions

Testing how file systems are mounted in the docker container and the
VM as well as what environment variables are passed in and how
arguments are passed in.

- The environment is set inside the entrypoint script, so any
  environment variables set when using the action is available.

- The GitHub action maps the following directories. The current
  working directory in bold:

  | Virtual Machine Directory                       | Container Directory     |
  | ----------------------------------------------- | ----------------------- |
  | `/var/run/docker.sock`                          | `/var/run/docker.sock`  |
  | `/home/runner/work/_temp/_github_home`          | `/github/home`          |
  | `/home/runner/work/_temp/_github_workflow`      | `/github/workflow`      |
  | `/home/runner/work/_temp/_runner_file_commands` | `/github/file_commands` |
  | **`/home/runner/work/super-meme/super-meme`**   | **`/github/workspace`** |
