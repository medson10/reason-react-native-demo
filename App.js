import React, { Component } from 'react'
import { View, Text } from 'react-native'
import { ApolloProvider } from 'react-apollo'
import { Provider as PaperProvider } from 'react-native-paper'
import { app as StackRouter } from './re/App.bs'
import apolloClient from './apollo'

export default class App extends Component {
  state = {
    hasError: false,
  }

  componentDidCatch = () => {
    this.setState({ hasError: true })
  }

  render() {
    if (this.state.hasError) {
      return (
        <View>
          <Text>Error!</Text>
        </View>
      )
    }

    return (
      <PaperProvider>
        <ApolloProvider client={apolloClient}>
          <StackRouter />
        </ApolloProvider>
      </PaperProvider>
    )
  }
}
