open BsReactNavigation;

open Config;

module Stack =
  StackNavigator.Create({
    open StackNavigator;

    type route = Config.route;

    let initialRoute = Countries;

    let getScreen = (route, navigation) =>
      switch (route) {
      | Countries => (<Countries navigation />, screenOptions(~title="Countries", ()))
      | CountryDetails(countryId) => (
          <CountryDetails navigation countryId />,
          screenOptions(~title="Country Details", ()),
        )
      };
  });

let render = Stack.render;
