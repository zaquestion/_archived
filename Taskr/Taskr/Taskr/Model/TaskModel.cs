using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Taskr.Model
{
    public class TaskModel
    {
        public string Description { get; set; }
        private double timeOfDay;
        public string TimeOfDay { get { return "Around: " + TimeSpan.FromHours(timeOfDay).ToString(@"%h\:mm"); } }
        
        public TaskModel(string Description, double TimeOfDay)
        {
            this.Description = Description;
            this.timeOfDay = TimeOfDay;
        }
    }
}
