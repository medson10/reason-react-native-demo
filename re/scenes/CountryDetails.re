open BsReactNative;

module Styles = {
  open Style;
  let wrapper =
    style([
      flex(1.),
      backgroundColor(String("#E0E1DD")),
      paddingTop(Pt(30.)),
    ]);
  let content =
    style([
      marginHorizontal(Pt(20.)),
    ]);
  let countryCode =
    style([fontSize(Float(20.)), color(String("#006")), marginVertical(Pt(10.))]);
  let countryName =
    style([fontSize(Float(18.)), color(String("#006")), marginVertical(Pt(10.))]);
  let languagesLabel =
    style([
      marginTop(Pt(10.)),
      fontSize(Float(18.)),
      color(String("#006")),
    ]);
  let languagesWrapper =
    style([
      borderStyle(Solid),
      borderWidth(StyleSheet.hairlineWidth),
      borderColor(String("#0D1B2A")),
      marginTop(Pt(25.)),
      padding(Pt(15.)),
    ]);
  let languageItem =
    style([
      fontSize(Float(15.)),
      color(String("#0D1B2A")),
      marginVertical(Pt(10.)),
    ]);
};

module Query = [%graphql
  {|
query CountryDetailsQuery($code: String!) {
  country(code: $code) {
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

let component = ReasonReact.statelessComponent("CountryDetails");

let make = (~navigation as _: Config.navigationProp, ~countryId, _children) => {
  ...component,
  render: _self => {
    let%Epitath {result} =
      c =>
        <QueryContainer variables=Query.make(~code=countryId, ())##variables>
          ...c
        </QueryContainer>;

    <SafeAreaView style=Styles.wrapper>
      {
        switch (result) {
        | Loading => <Loader />
        | Error(_) => <ErrorMessage />
        | Data(data) =>
          Belt.Option.mapWithDefault(data##country, ReasonReact.null, country =>
            <View style=Styles.content>
              <Paper.Text style=Styles.countryCode>
                {
                  ReasonReact.string(
                    "Code: " ++ Belt.Option.getWithDefault(country##code, ""),
                  )
                }
              </Paper.Text>
              <Paper.Text style=Styles.countryName>
                {
                  ReasonReact.string(
                    "Name: " ++ Belt.Option.getWithDefault(country##name, ""),
                  )
                }
              </Paper.Text>
              <Paper.Text style=Styles.languagesLabel>{ReasonReact.string("Languages:")}</Paper.Text>
              <View style=Styles.languagesWrapper>
              {
                country##languages
                ->Belt.Option.getWithDefault([||])
                ->Belt.Array.map(language =>
                    Belt.Option.mapWithDefault(
                      language,
                      ReasonReact.null,
                      languageData =>
                          <Paper.Text style=Styles.languageItem key={Belt.Option.getWithDefault(languageData##code, "")}>
                          {
                            Belt.Option.getWithDefault(languageData##name, "")
                            ->ReasonReact.string
                          }
                          </Paper.Text>
                    )
                  )
                ->ReasonReact.array
              }
              </View>
            </View>
          )
        }
      }
    </SafeAreaView>;
  },
};
