using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GenericUtilities
{
    public class ArgumentParser
    {
        private bool helpInitialized = false;
        private string[] helpNames; //Names for which to match a help command against. Set in InitializeHelp

        private List<Argument> _args = new List<Argument>();

        /// <summary>
        /// Tell the parser what to do when help is called in it's default case
        /// Help can be called following a command or on its own
        /// In either case the string being acted on contains all of the fomatted help text
        /// Format:
        /// name1, name2, name3, ...
        ///     [provided help text]
        /// </summary>
        /// <param name="Act"></param>
        public void InitializeHelp(Action<string> Act)
        {
            Argument helpArg = new Argument
            (
                _args,
                (args, p) =>
                {
                    StringBuilder sb = new StringBuilder();

                    sb.AppendLine();

                    if (null == p)
                    {
                        var argsCasted = (List<Argument>)args;

                        foreach (Argument arg in argsCasted)
                        {
                            sb.Append(arg.GetNames());

                            sb.AppendLine();

                            sb.AppendLine("\t" + arg.HelpText);

                            sb.AppendLine();
                        }
                    }
                    else
                    {
                        sb.AppendLine(p);
                    }

                    Act(sb.ToString());
                },
                "Will bring up this text",
                "help",
                "/?",
                "-?",
                "--help"
           );

            InitializeHelp(helpArg);
        }

        /// <summary>
        /// Allows the user to define there own help argument
        /// The parameter will be the names and help text on the argument help is call on
        /// When help is called on its own you are responsible for what happens
        /// </summary>
        /// <param name="helpArg"></param>
        public void InitializeHelp(Argument helpArg)
        {
            if (helpInitialized || null != helpNames)
                throw new Exception("Help is already Initilized");
            
            helpNames = helpArg.Names;

            _args.Insert(0, helpArg);

            helpInitialized = true;
        }
        
        /// <summary>
        /// Adds an argument to the parser
        /// </summary>
        /// <param name="inArgs">1 or more args to add</param>
        public void AddArgument(params Argument[] inArgs)
        {
            Argument DupArg = FindDup(_args, inArgs);

            if (DupArg != null)
            {
                throw new Exception("Duplicate argument detected, one of: " + DupArg.GetNames());
            }

            foreach (Argument arg in inArgs)
            {
                if (arg.Names == helpNames)
                    continue;
                _args.Add(arg);
            }
        }

        public void Parse(string[] StringArgs)
        {
            Parse(StringArgs, s => { throw new ArgumentException(s); });
        }

        public void Parse(string[] StringArgs, Action<string> NoMatchAction)
        {
            List<Argument> ToInvoke = new List<Argument>();

            if (_args.Count() < 1)
            {
                throw new NullReferenceException("Attempted to parse with out adding any arguments to the parser");
            }

            //match an argument
            Argument match = null;

            foreach (string sArg in StringArgs)
            {
                if (null == match) //Have we selected a command/option
                {
                    if (null == (match = this.FindArg(sArg))) //Did we find one?
                    {
                        NoMatchAction("Invalid argument: " + sArg);
                    }
                    else
                    {
                        //well we have a match now
                    }
                }
                else
                {
                    //we already have a match
                    Argument NextArg = this.FindArg(sArg);

                    //Special case fot the help argument
                    if (helpNames != null && match.Names.Contains(helpNames.First()))
                    {
                        match.Invoke();

                        return;
                    }

                    if (null == NextArg)
                    {
                        match.Parameter = sArg;
                        ToInvoke.Add(match);

                        match = null;
                        continue;
                    }
                    else
                    {
                        //Special case fot the help argument
                        if (helpNames != null && NextArg.Names.Contains(helpNames.First()))
                        {
                            StringBuilder sb = new StringBuilder();
                            sb.Append(match.GetNames());
                            sb.AppendLine();

                            sb.AppendLine("\t" + match.HelpText);

                            NextArg.Parameter = sb.ToString();
                            NextArg.Invoke();

                            return;
                        }

                        //Else assume 'match' is a switch and has no parameter
                        //For now handling for this case will fall on the arguement implementation
                        
                        ToInvoke.Add(match);

                        match = NextArg;
                        continue;
                    }
                }
            }

            if (null != match)
            {
                ToInvoke.Add(match);
            }

            foreach (Argument arg in ToInvoke)
            {
                arg.Invoke();
            }
        }

        /// <summary>
        /// Uses the internal (set) list of argument to match
        /// </summary>
        /// <param name="Arg">string argument to match against</param>
        /// <returns>matched argument or null</returns>
        public Argument FindArg(string Arg)
        {
            foreach (Argument arg in _args)
            {
                foreach (string name in arg.Names)
                {
                    if (Arg.Equals(name, StringComparison.CurrentCultureIgnoreCase)) { return arg; }
                }
            }

            return null;
        }
    
        /// <summary>
        /// Checks for duplicate in argument names 
        /// </summary>
        /// <param name="args">args to check against</param>
        /// <param name="Arg">Argument to check</param>
        /// <returns>First Duplicate Argument if a dup is found else null</returns>
        private Argument FindDup(IList<Argument> args, params Argument[] Args)
        {
            foreach (Argument arg in args)
            {
                foreach (Argument Arg in Args)
                {
                    foreach (string namearg in arg.Names)
                    {
                        foreach (string nameArg in Arg.Names)
                        {
                            if (namearg.Equals(nameArg, StringComparison.CurrentCultureIgnoreCase))
                            {
                                return Arg;
                            }
                        }
                    }
                }
            }

            return null;
        }
    }

    public class Argument
    {
        #region Fields

        private string parameter; //parameter to pass into act
        private string[] names;
        private string help;

        private object obj;
        private Action<object, string> act;

        #endregion

        #region Properties

        public string[] Names
        {
            get { return names; }
        }

        public string HelpText
        {
            get { return help; }
        }

        public string Parameter
        {
            get { return parameter; }
            set { parameter = value; }
        }

        #endregion

        public Argument(object obj, Action<object, string> act, string help, params string[] names)
        {
            this.names = names;
            this.help = help;

            this.obj = obj;
            this.act = act;
        }

        public void Invoke()
        {
            act(obj, parameter);
        }

        /// <summary>
        /// Gets the names associated with the Argument 
        /// </summary>
        /// <returns>Comma seperated string of names</returns>
        public string GetNames()
        {

            StringBuilder sb = new StringBuilder();
            foreach (string name in this.Names)
            {
                sb.Append(name + ", ");
            }

            sb.Remove(sb.Length - 2, 2);
            
            return sb.ToString();
        }
    }
}
