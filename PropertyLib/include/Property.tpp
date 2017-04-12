template<typename type>
void defaultSetter(const type & value, type & destination)
{
	destination = value;
}

template<typename type>
type defaultGetter(const type & value)
{
	return value;
}

template<typename type>
bool defaultInputMethod(std::ifstream & in, Any & value)
{
	type newValue;

	in >> newValue;
	value = newValue;

	return true;
}

template<typename type>
bool defaultOutputMethod(std::ofstream & out, Any & value)
{
	out << anyCast<type>(value);

	return true;
}



// Constructors

template<typename InterfaceType, typename StoredType>
Property<InterfaceType, StoredType>::Property()
{
	this->inputMethod = defaultInputMethod<InterfaceType>;
	this->outputMethod = defaultOutputMethod<InterfaceType>;
}

template<typename InterfaceType, typename StoredType>
Property<InterfaceType, StoredType>::Property(SetterType setterFunction, GetterType getterFunction)
{
	this->setter = setterFunction;
	this->getter = getterFunction;

	this->inputMethod = defaultInputMethod<InterfaceType>;
	this->outputMethod = defaultOutputMethod<InterfaceType>;
}


// Set setter and getter
template<typename InterfaceType, typename StoredType>
void Property<InterfaceType, StoredType>::setSetterFunction( SetterType setterFunction )
{
	this->setter = setterFunction;
}

template<typename InterfaceType, typename StoredType>
void Property<InterfaceType, StoredType>::setGetterFunction( GetterType getterFunction )
{
	this->getter = getterFunction;
}

// Set inputMethod and outputMethod
template<typename InterfaceType, typename StoredType>
void Property<InterfaceType, StoredType>::setInputMethod( InputMethodType newInputMethod )
{
	this->inputMethod = newInputMethod;
}

template<typename InterfaceType, typename StoredType>
void Property<InterfaceType, StoredType>::setOutputMethod( OutputMethodType newOutputMethod )
{
	this->outputMethod = newOutputMethod;
}


// Only one type

// Constructors
// If types are equal, we are allowed to use defaultSetter and defaultGetter (copy setter and getters)
template<typename type>
Property<type>::Property()
	: Property<type, type>()
{
	this->setter = defaultSetter<type>;
	this->getter = defaultGetter<type>;
}

// If types are equal, we are allowed to use defaultSetter and defaultGetter (copy setter and getters)
template<typename type>
Property<type>::Property(SetterType setterFunction, GetterType getterFunction)
	: Property<type, type>(setterFunction, getterFunction)
{
}
