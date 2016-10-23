using System;
using System.Collections.Generic;
using System.IO.IsolatedStorage;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Navigation;
using Taskr.Model;

namespace Taskr.ViewModel
{
    public class MainViewModel
    {
        public String DescriptionTextBox { get; set; }
        public double TimeOfDaySlider { get; set; }


        public MainViewModel()
        {
        }

        public DelegateCommand Manage_PressedCommand
        {
            get { return new DelegateCommand((object o) => { App.RootFrame.Navigate(new Uri("/View/ManagePage.xaml", UriKind.Relative)); }); }
        }

        public DelegateCommand Add_PressedCommand
        {
            get { return new DelegateCommand(AddTask); }
        }

        public void AddTask(object o)
        {
            byte[] hash = new SHA256Managed().ComputeHash(Encoding.Unicode.GetBytes(DescriptionTextBox));
            string hashString = Encoding.Unicode.GetString(hash, 0, DescriptionTextBox.Length);

            if (!IsolatedStorageSettings.ApplicationSettings.Contains(hashString))
            {
                IsolatedStorageSettings.ApplicationSettings.Add(hashString, new TaskModel(DescriptionTextBox, TimeOfDaySlider));
            }
            else
            {
                MessageBox.Show("Task with description already exists in Taskr");
            }
        }
    }
}
