using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Taskr
{

    public class DelegateCommand : ICommand
    {
        Action<object> executeAction;
        Func<object, bool> canExecuteAction;

        public DelegateCommand(Action<object> executeAction)
        {
            this.executeAction = executeAction;
            canExecuteAction = (object o) => { return true; };
        }

        public DelegateCommand(Action<object> executeAction, Func<object, bool> canExecuteAction)
        {
            this.executeAction = executeAction;
            this.canExecuteAction = canExecuteAction;
        }

        public bool CanExecute(object parameter)
        {
            return canExecuteAction(parameter);
        }

        public event EventHandler CanExecuteChanged;

        public void Execute(object parameter)
        {
            executeAction(parameter);
        }
    }
}
