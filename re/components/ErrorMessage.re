open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      flexDirection(Column),
      alignItems(Center),
      justifyContent(Center),
    ]);
  let message = style([fontSize(Float(20.)), textAlign(Center)]);
};

let component = ReasonReact.statelessComponent("ErrorMessage");

let make = (~message="Something went wrong!", _children) => {
  ...component,
  render: _self =>
    <View style=Styles.wrapper>
      <Paper.Text style=Styles.message>
        {ReasonReact.string(message)}
      </Paper.Text>
    </View>,
};
