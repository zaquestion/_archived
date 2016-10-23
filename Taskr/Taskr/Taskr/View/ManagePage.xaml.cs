using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Taskr.ViewModel;

namespace Taskr
{
    public partial class ManagePage : PhoneApplicationPage
    {
        public ManagePage()
        {
            InitializeComponent();

            DataContext = new ManageViewModel();
        }
    }
}