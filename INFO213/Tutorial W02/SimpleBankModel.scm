jadeVersionNumber "22.0.03";
schemaDefinition
SimpleBankModel subschemaOf RootSchema completeDefinition;
	setModifiedTimeStamp "jorda" "22.0.03" 2024:03:01:13:15:18.152;
localeDefinitions
	5129 "English (New Zealand)" schemaDefaultLocale;
	setModifiedTimeStamp "jorda" "22.0.03" 2024:03:01:13:15:18.132;
typeHeaders
	SimpleBankModel subclassOf RootSchemaApp transient, sharedTransientAllowed, transientAllowed, subclassSharedTransientAllowed, subclassTransientAllowed, number = 2055;
	Customer subclassOf Object number = 2058;
	GSimpleBankModel subclassOf RootSchemaGlobal transient, sharedTransientAllowed, transientAllowed, subclassSharedTransientAllowed, subclassTransientAllowed, number = 2056;
	SSimpleBankModel subclassOf RootSchemaSession transient, sharedTransientAllowed, transientAllowed, subclassSharedTransientAllowed, subclassTransientAllowed, number = 2057;
membershipDefinitions
typeDefinitions
	Object completeDefinition
	(
	)
	Application completeDefinition
	(
	)
	RootSchemaApp completeDefinition
	(
	)
	SimpleBankModel completeDefinition
	(
		setModifiedTimeStamp "jorda" "22.0.03" 2024:03:01:13:15:18.151;
	)
	Customer completeDefinition
	(
		setModifiedTimeStamp "jorda" "22.0.03" 2024:03:01:13:17:06.868;
	)
	Global completeDefinition
	(
	)
	RootSchemaGlobal completeDefinition
	(
	)
	GSimpleBankModel completeDefinition
	(
		setModifiedTimeStamp "jorda" "22.0.03" 2024:03:01:13:15:18.151;
	)
	WebSession completeDefinition
	(
	)
	RootSchemaSession completeDefinition
	(
		setModifiedTimeStamp "<unknown>" "6.1.00" 20031119 2003:12:01:13:54:02.270;
	)
	SSimpleBankModel completeDefinition
	(
		setModifiedTimeStamp "jorda" "22.0.03" 2024:03:01:13:15:18.151;
	)
databaseDefinitions
	SimpleBankModelDb
	(
	setModifiedTimeStamp "jorda" "22.0.03" 2024:03:01:13:15:18.152;
	databaseFileDefinitions
		"simplebankcustomer" number = 54;
		setModifiedTimeStamp "jorda" "22.0.03" 2024:03:01:13:16:25.904;
		"simplebankmodel" number = 53;
		setModifiedTimeStamp "jorda" "22.0.03" 2024:03:01:13:15:18.152;
	defaultFileDefinition "simplebankmodel";
	classMapDefinitions
		Customer in "simplebankcustomer";
		GSimpleBankModel in "simplebankmodel";
		SSimpleBankModel in "_environ";
		SimpleBankModel in "_usergui";
	)
typeSources
