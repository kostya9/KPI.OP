using System;
using System.Windows.Input;

namespace Spells.Editor
{
    class GenericICommand<T> : ICommand
    {
        private readonly Action<T> _targetExecuteMethod;
        private readonly Func<T, bool> _targetCanExecuteMethod;
        public event EventHandler CanExecuteChanged;

        public GenericICommand(Action<T> targetExecuteMethod)
        {
            _targetExecuteMethod = targetExecuteMethod;
        }

        public GenericICommand(Action<T> targetExecuteMethod,
            Func<T, bool> targetCanExecuteMethod) : this(targetExecuteMethod)
        {
            _targetCanExecuteMethod = targetCanExecuteMethod;
        }

        public bool CanExecute(object parameter)
        {
            if (_targetCanExecuteMethod != null)
                return _targetCanExecuteMethod((T)parameter);

            if (_targetExecuteMethod != null)
                return true;

            return false;
        }

        public void Execute(object parameter)
        {
            _targetExecuteMethod?.Invoke((T)parameter);
        }

        public void RaiseCanExecuteChanged()
        {
            CanExecuteChanged?.Invoke(this, EventArgs.Empty);
        }

        
    }
}
