const React = require('react');

const Hello = _ => <h1>Hello</h1>;
const World = _ => <h2>World!</h2>;

class Greet extends React.Component {
		render() {
				return <div><Hello /><World /></div>;
		}
}
