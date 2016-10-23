using System;
using System.Collections.ObjectModel;
using Taskr.Model;
using System.IO.IsolatedStorage;

namespace Taskr.ViewModel
{
    public class ManageViewModel
    {
        public ObservableCollection<TaskModel> Tasks { get; set; }

        public ManageViewModel()
        {
            GetTasks();
        }

        public void GetTasks()
        {
            if(IsolatedStorageSettings.ApplicationSettings.Count > 0)
            {
                GetSavedTasks();
            }
            else
            {
                GetDefaultTasks();
            }
        }

        public void GetDefaultTasks()
        {
            ObservableCollection<TaskModel> a = new ObservableCollection<TaskModel>();

            a.Add(new TaskModel("No Tasks", 0));

            Tasks = a;
        }

        public void GetSavedTasks()
        {
            ObservableCollection<TaskModel> a = new ObservableCollection<TaskModel>();
            
            foreach(Object o in IsolatedStorageSettings.ApplicationSettings.Values)
            {
                a.Add((TaskModel)o);
            }

            Tasks = a;
        }
    }
}
