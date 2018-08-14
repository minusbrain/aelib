#ifndef _GIT_H_
#define _GIT_H_

#include <experimental/filesystem>

namespace std {
    namespace filesystem = experimental::filesystem;
}

namespace ae {

class GitRepoManager
{
public:
	GitRepoManager(std::filesystem::path repo_location): _repo(repo_location), _callCdToRepo()
	{
		_callCdToRepo.append("cd ");
		_callCdToRepo.append(repo_location.string());
	}

	~GitRepoManager() {};

	void callRawCommand(std::string cmd) {
		executeCmdInRepo(cmd);
	}

	void initRepo() {
		executeCmdInRepo("git init");
	}

	void stageAllChanges() {
		executeCmdInRepo("git add .");
	}

	void commit(std::string commit_message) {
		executeCmdInRepo(std::string("git commit -m '") + commit_message + "'");
	}

private:
	void executeCmdInRepo(std::string cmd) {
		std::string call;
		call.append(_callCdToRepo);
		call.append(" && ");
		call.append(cmd);
		system(call.c_str());
	}

	std::filesystem::path _repo;
	std::string _callCdToRepo;
};
}

#endif //_GIT_H_