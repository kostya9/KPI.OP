using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Spells.Editor
{
    class ArgumentlessICommand : ICommand
    {
        private readonly Action _targetExecuteMethod;
        private readonly Func<bool> _targetCanExecuteMethod;
        public event EventHandler CanExecuteChanged;

        public ArgumentlessICommand(Action targetExecuteMethod)
        {
            _targetExecuteMethod = targetExecuteMethod;
        }

        public ArgumentlessICommand(Action targetExecuteMethod,
            Func<bool> targetCanExecuteMethod) : this(targetExecuteMethod)
        {
            _targetCanExecuteMethod = targetCanExecuteMethod;
        }

        public bool CanExecute(object parameter = null)
        {
            if (_targetCanExecuteMethod != null)
                return _targetCanExecuteMethod();

            if (_targetExecuteMethod != null)
                return true;

            return false;
        }

        public void Execute(object parameter = null)
        {
            _targetExecuteMethod?.Invoke();
        }

        public void RaiseCanExecuteChanged()
        {
            CanExecuteChanged?.Invoke(this, EventArgs.Empty);
        }
    }
}
