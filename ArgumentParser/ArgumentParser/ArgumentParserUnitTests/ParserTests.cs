using System;
using GenericUtilities;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace ArgumentParserUnitTests
{
    [TestClass]
    public class ParserTests
    {
        [TestMethod]
        public void NoHelpArgumentBVT()
        {
            ArgumentParser Parser = new ArgumentParser();

            string expectedValue = "Hello, World";
            string actualValue = null;

            Argument arg = new Argument(", World", (s, p) => { actualValue = (p + (string)s);  }, "useless message", "test", "t", "-t", "/t");
        
            Parser.AddArgument(arg);

            Parser.Parse(new string[] { "test", "Hello"});

            Assert.AreEqual(actualValue, expectedValue);
        }

        [TestMethod]
        public void DisplayHelp()
        {
            ArgumentParser Parser = new ArgumentParser();

            string expectedValue = "\r\ntest, t\r\n\tthis is a help message\r\n\r\n";
            string actualValue = null;

            Parser.InitializeHelp(s => { actualValue = s; });

            Argument arg = new Argument(", World", (s, p) => { }, "this is a help message", "test", "t");

            Parser.AddArgument(arg);

            Parser.Parse(new string[] { "test", "help"});

            Assert.AreEqual(expectedValue, actualValue);
        }

        [TestMethod]
        public void InitializeDefaultHelpNoArguments()
        {
            ArgumentParser Parser = new ArgumentParser();

            string expectedValue = "\r\nhelp, /?, -?, --help\r\n\tWill bring up this text\r\n\r\n";
            string actualValue = null;

            Parser.InitializeHelp(s => { actualValue = s; });

            Parser.Parse(new string[] { "help" });

            Assert.AreEqual(expectedValue, actualValue);
        }

        //ExpectedExcpetion not used so that the text of the exception could be verified. The purpose of this test is to ensure the user is informed about what happend
        [TestMethod]
        public void NoArguments()
        {
            ArgumentParser Parser = new ArgumentParser();

            try
            {
                Parser.Parse(new string[] { "test", "hello" });
            }
            catch (NullReferenceException e)
            {
                Assert.AreEqual("Attempted to parse with out adding any arguments to the parser", e.Message);
            }
            catch (Exception e)
            {
                Assert.Fail("Unexpected Exception:" + e.Message);
            }
        }
    }
}
