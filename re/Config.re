open BsReactNavigation;

type route =
  | Countries
  | CountryDetails(string);

type navigationProp = StackNavigator.navigation(route);

type navigation = StackNavigator.navigation(route);
