#include <map>

#include "ParameterSetImpl.hxx"
#include "Parameters.hxx"

ParameterSetImpl::ParameterSetImpl() {}

ParameterSetImpl::~ParameterSetImpl() {}

ParameterSetImpl::ParameterSetImpl(const ParameterSetImpl& other) {
  dummy = other.dummy;
  parameters = other.parameters;
}

Parameters::Parameter& ParameterSetImpl::getParameter(std::string name)
{
  dummy = Parameters::Parameter("", NULL);
  std::map<std::string, Parameters::Parameter>::iterator iter =  parameters.find(name);
  if(iter == parameters.end())
    return dummy;
  else
    return iter->second;
}

bool ParameterSetImpl::setParameter(std::string name, boost::any value)
{
  std::map<std::string, Parameters::Parameter>::iterator iter =  parameters.find(name);
  if(iter == parameters.end())
  {
    parameters[name].value = value;
    parameters[name].name = name;
    return false;
  }
  else
  {
    iter->second.value=value;
    return true;
  }
}

/*bool ParameterSetImpl::setParameter(Parameters::Parameter& other)
{
  setParameter(other.name, other.value);
}*/

std::vector<std::string> ParameterSetImpl::getParameterNames()
{
  std::vector<std::string> parameterNames;
  for(std::map<std::string, Parameters::Parameter>::iterator iter = parameters.begin(); iter != parameters.end(); iter++)
  {
    parameterNames.push_back(iter->first);
  }
  return parameterNames;
}
