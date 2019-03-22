open BsReactNative;

let component = ReasonReact.statelessComponent("Loader");

let make = _children => {
  ...component,
  render: _self =>
    <View
      style=Style.(
        style([
          flex(1.),
          flexDirection(Column),
          alignItems(Center),
          justifyContent(Center),
        ])
      )>
      <ActivityIndicator size=`large />
    </View>,
};
