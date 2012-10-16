namespace Smartmatic
{
namespace Functionality
{

template <class TMenuOptionDescriptor>
FunctionalityManager<TMenuOptionDescriptor>::FunctionalityManager()
{

}

template <class TMenuOptionDescriptor>
FunctionalityManager<TMenuOptionDescriptor>::~FunctionalityManager()
{
    functionalities.clear();
}

template <class TMenuOptionDescriptor>
bool FunctionalityManager<TMenuOptionDescriptor>::ExecuteOptionSelected(TMenuOptionDescriptor menuDesc)
{
    bool result = false;

    try
    {
        Functionality<TMenuOptionDescriptor>* pntr = functionalities.find(menuDesc)->second;

        if(pntr != NULL)
        {
            if(pntr->CanExecute())
            {
                bool challengeResult = false;
                if(pntr->ChallengeIsEnable())
                {
                    challengeResult = ExecuteChallenge(pntr);
                }
                else
                    challengeResult = true;

                if(challengeResult)
                {
                    pntr->Do();

                    if(pntr->LockMachine())
                    {
                        result = true;
                    }
                }
            }
            else
            {
                pntr->DisplayUnableMessage();
            }
        }
        else
        {
            std::cout << "functionality is null" << std::endl;
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "FATAL - " << e.what() << std::endl;
    }

    return result;
}

template <class TMenuOptionDescriptor>
void FunctionalityManager<TMenuOptionDescriptor>::Register(Functionality<TMenuOptionDescriptor> *funct)
{
    try
    {
        if (funct != NULL)
        {
            TMenuOptionDescriptor option = funct->GetMenuOptionType();
            funct->LockMachineSigc().connect(sigc::mem_fun(this, &FunctionalityManager::LockMachineSignal));
            functionalities.insert( std::pair<TMenuOptionDescriptor, Functionality<TMenuOptionDescriptor>* >(option, funct) );
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "FATAL - " << e.what() << std::endl;
    }
}

template <class TMenuOptionDescriptor>
bool FunctionalityManager<TMenuOptionDescriptor>::ExecuteChallenge(Functionality<TMenuOptionDescriptor>* funct)
{
    return true;
}

template <class TMenuOptionDescriptor>
void FunctionalityManager<TMenuOptionDescriptor>::LockMachineSignal()
{
    m_lock_machine.emit();
}

template <class TMenuOptionDescriptor>
sigc::signal<void> FunctionalityManager<TMenuOptionDescriptor>::LockMachine()
{
    return m_lock_machine;
}
}
}
