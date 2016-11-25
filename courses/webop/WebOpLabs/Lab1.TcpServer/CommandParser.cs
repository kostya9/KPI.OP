using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Lab1.TcpServer
{
    /// <summary>
    /// Parses a command. Assumes it is in format *command* -*option* *value* -*option* *value* ...
    /// </summary>
    public class CommandParser
    {
        public string MainCommand { get; }
        public IDictionary<string, string> Options { get; }

        public CommandParser(string command)
        {
            this.MainCommand = GetMainCommand(command);
            var indexOfOptions = MainCommand.Length + 1;
            if (command.Length == MainCommand.Length)
            {
                this.Options = new Dictionary<string, string>();
                return;
            }
            var options = command.Substring(indexOfOptions);
            this.Options = GetOptions(options);
        }

        private IDictionary<string, string> GetOptions(string options)
        {
            var optionsDictionary = new Dictionary<string, string>();
            var optionsList = options.Split('-');
            foreach (var option in optionsList)
            {
                if (option == "")
                    continue;

                var optionWords = option.Split(' ');

                if (optionWords.Length < 2)
                {
                    optionsDictionary[optionWords[0]] = "";
                    continue;
                }

                optionsDictionary[optionWords[0]] = optionWords[1];
            }
            return optionsDictionary;
        }

        private string GetMainCommand(string command)
        {
            var indexOfOptions = command.IndexOf(" -", StringComparison.Ordinal);
            var mainCommand = indexOfOptions >= 0  ? command.Substring(0, indexOfOptions) : command;
            return mainCommand;
        }
    }
}
