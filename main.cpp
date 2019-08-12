#include <iostream>
#include <vector>
#include <string>

#define EXIT_STRING "exit"
#define SUBCOMMAND_NF "Subcommand not found"
#define COMMAND_NF "Command not found"

class Command {
public:
	Command(const char* name) {
		this->name = name;
	}

	virtual void call(std::vector<std::string> args) = 0;

	inline std::string getName() const {
		return this->name;
	}

private:
	std::string name;
};

class TestCommand : public Command {
public:
	TestCommand()
		: Command("test") {}

	int test = 0;

	void call(std::vector<std::string> args) override {
		std::cout << "Command Test executed. Arguments:" << std::endl;
		for (std::string str : args) {
			std::cout << str << std::endl;
			test++;
		}
	}
};

class CommandHandler {
public:
	CommandHandler() {
		registerCommands();
	}

	~CommandHandler() {
		destroyCommands();
	}

	Command* getCommand(const char* name) {
		for (Command* cmd : commandList) {
			if (name == cmd->getName())
				return cmd;
		}
		return nullptr;
	}

private:
	std::vector<Command*> commandList;

	void registerCommands() {
		commandList.push_back(new TestCommand);
	}

	void destroyCommands() {
		for (Command* cmd : commandList) {
			delete cmd;
		}
	}
};

std::vector<std::string> _split(std::string str, std::string del) // Function from high level programming languages like c# or js
{
	std::vector<std::string> splits;
	size_t pos;
	while ((pos = str.find(del)) != std::string::npos) {
		splits.push_back(str.substr(0, pos));
		str.erase(0, pos + del.length());
	}
	splits.push_back(str);
	return splits;
}

int main(int argc, char** argv) {
	CommandHandler hCmd;

	Command* cmd;

	std::string input;

	if (argc == 1) {
		do
		{
			input = "";
			char c;
			while ((c = std::cin.get()) != '\n') {
				input += c;
			}
			std::vector<std::string> args = _split(input, " ");
			cmd = hCmd.getCommand(args[0].c_str());
			args.erase(args.begin());
			if (cmd != nullptr) {
				cmd->call(args);
			}
			else if(input != EXIT_STRING) {
				std::cout << COMMAND_NF << std::endl;
			}
		} while (input != EXIT_STRING);
	}
	else if (argc > 1) {
		std::vector<std::string> args(argv + 1, argv + argc);
		
		CommandHandler hCmd;
		Command* cmd = hCmd.getCommand(argv[1]);
		if (cmd != nullptr) {
			args.erase(args.begin(), args.begin() + 1);
			cmd->call(args);
		}
		else {
			std::cout << SUBCOMMAND_NF << std::endl;
		}
	}
	return 0;
}