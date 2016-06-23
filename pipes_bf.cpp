#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
#include <fcntl.h>

std::vector<std::string> ParseSingleCmd(const std::string& cmd) {
  std::vector<std::string> res;

  size_t old_pos = cmd.find_first_not_of(' ');
  size_t pos;
  while (std::string::npos != (pos = cmd.find(' ', old_pos))) {
    res.push_back(cmd.substr(old_pos, pos - old_pos));
    old_pos = cmd.find_first_not_of(' ', pos + 1);
  }
  if (old_pos < cmd.size()) {
    res.push_back(cmd.substr(old_pos));
  }

  return res;
}

std::vector<std::vector<std::string> > ParseCmd(const std::string& cmd) {
  std::vector<std::vector<std::string> > res;

  size_t old_pos = 0, pos;
  while (std::string::npos != (pos = cmd.find('|', old_pos))) {
    res.push_back(ParseSingleCmd(cmd.substr(old_pos, pos - old_pos)));
    old_pos = pos + 1;
  }
  res.push_back(ParseSingleCmd(cmd.substr(old_pos)));

  return res;
}

void Run(const std::vector<std::string>& command) {
  char** argv = new char*[command.size() + 1];

  char** pos = argv;
  for (const auto& word : command) {
    *pos++ = strdup(word.c_str());
  }
  *pos = NULL;

//  for (int i = 0; i < command.size(); ++i) {
//    std::cerr << argv[i] << " ";
//  }
//  std::cerr << std::endl;

  if (execvp(argv[0], argv) < 0) {
    perror("execvp");
    fprintf(stderr, "%s", argv[0]);
    exit(EXIT_FAILURE);
  }
}

int main() {
  std::string cmd;
  std::getline(std::cin, cmd);
  const std::vector<std::vector<std::string> > commands = ParseCmd(cmd);

  for (size_t idx = 0; idx + 1 < commands.size(); ++idx) {
    int fd[2];
    pipe(fd);

    if (fork()) {
      close(fd[0]);
      dup2(fd[1], STDOUT_FILENO);
      close(fd[1]);

      Run(commands[idx]);
    }

    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
  }

  int outfd = open("/home/box/result.out", O_WRONLY | O_CREAT | O_TRUNC);
  dup2(outfd, STDOUT_FILENO);
  close(outfd);

  Run(commands.back());

  return 0;
}
