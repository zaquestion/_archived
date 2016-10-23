using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Net;
using System.Text.RegularExpressions;
using System.IO;
using System.Threading;

namespace UrbanDictionaryScrapper
{
    class Program
    {
        static FileStream file = File.Open("WordListSpaces.txt", FileMode.OpenOrCreate);
        static StreamWriter sw = new StreamWriter(file);
        static void Main(string[] args)
        {
            WebClient wc = new WebClient();
                //<div id="not_defined_yet">
                //while (true)
                //{
                    //string cpage = wc.DownloadString("http://www.urbandictionary.com/define.php?term=" + Console.ReadLine());
                    //Console.WriteLine(cpage.Contains("<div id='not_defined_yet'>") ? "no" : "yes");
                //}

                

                for (char c = 'A'; c <= 'Z'; c++)
                {
                    string cpage = "";
                down1:
                    try
                    {
                        Thread.Sleep(10+0);
                        cpage = wc.DownloadString("http://www.urbandictionary.com/browse.php?character=" + c + "&page=1");
                    }
                    catch
                    {
                        goto down1;
                    }

                    int max = 0;
                    foreach (Match m in new Regex(@"<a href=""/browse\.php\?character=" + c + @"&amp;page=\d+"">(?<number>\d+)</a>", RegexOptions.ExplicitCapture | RegexOptions.Multiline).Matches(cpage)) max = max < Convert.ToInt32(m.Groups["number"].Value) ? Convert.ToInt32(m.Groups["number"].Value) : max;
        
                    //<a href="/browse.php?character=A&amp;page=400">400</a>
                    //<a href="/browse.php?character=A&amp;page=400">400</a>

                    GrabWords(new Regex(@"<li>(<b>)?<a href=""/define\.php\?term=[A-Za-z]+"">(?<word>[A-Za-z]+)</a>(</b>)?</li>").Matches(cpage));

                    for (int i = 1; i < max; i++)
                    {
                    down2:
                        try
                        {
                            Thread.Sleep(100);
                            cpage = wc.DownloadString("http://www.urbandictionary.com/browse.php?character=" + c + "&page=" + i);
                        }
                        catch
                        {
                            goto down2;
                        }
                    GrabWords(new Regex(@"<li>(<b>)?<a href=""/define\.php\?term=[A-Za-z]+"">(?<word>[A-Za-z]+)</a>(</b>)?</li>").Matches(cpage));


                        Console.WriteLine("Letter: " + c + " Page: " + i);
                    }
                    //<li><a href="/define.php?term=A-">A-</a></li>
                }
            
        }

        private static void GrabWords(MatchCollection mc)
        {
            foreach (Match m in mc) sw.WriteLine(m.Groups["word"].Value);
        }
    }
}