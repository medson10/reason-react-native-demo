open BsReactNative;

module Styles = {
  open Style;
  let wrapper = style([flex(1.), backgroundColor(String("#E0E1DD"))]);
  let countryList =
    style([marginHorizontal(Pt(20.)), paddingTop(Pt(10.))]);
  let countryItem =
    style([
      fontSize(Float(18.)),
      color(String("#006")),
      marginVertical(Pt(10.)),
    ]);
};

module Query = [%graphql
  {|
query CountriesQuery {
  countries {
    code
    name
    languages {
      code
      name
    }
  }
}
|}
];

module QueryContainer = ReasonApollo.CreateQuery(Query);

let component = ReasonReact.statelessComponent("Countries");

let make = (~navigation: Config.navigationProp, _children) => {
  ...component,
  render: _self =>
    <SafeAreaView style=Styles.wrapper>
      <QueryContainer>
        ...{
             ({result}) =>
               switch (result) {
               | Loading => <Loader />
               | Error(_) => <ErrorMessage />
               | Data(data) =>
                 <ScrollView style=Styles.countryList>
                 {
                   Belt.Option.getWithDefault(data##countries, [||])
                   ->Belt.Array.map(country =>
                       Belt.Option.map(country, countryData =>
                         <TouchableOpacity
                           activeOpacity=0.8
                           key={
                             Belt.Option.getWithDefault(countryData##code, "")
                           }
                           onPress=(
                             _ =>
                               navigation.push(
                                 CountryDetails(
                                   Belt.Option.getWithDefault(
                                     countryData##code,
                                     "",
                                   ),
                                 ),
                               )
                           )>
                           <Paper.Text style=Styles.countryItem>
                             {
                               ReasonReact.string(
                                 countryData##name
                                 ->Belt.Option.getWithDefault(""),
                               )
                             }
                           </Paper.Text>
                         </TouchableOpacity>
                       )
                       ->Belt.Option.getWithDefault(ReasonReact.null)
                     )
                   ->ReasonReact.array
                 }
                 </ScrollView>
               }
           }
      </QueryContainer>
    </SafeAreaView>,
};
