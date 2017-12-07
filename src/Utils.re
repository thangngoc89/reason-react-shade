let strEl = ReasonReact.stringToElement;

let floatToString = (value: float) => value |> int_of_float |> string_of_int;

let valueFromEvent = (evt) : string => (
                                         evt
                                         |> ReactEventRe.Form.target
                                         |> ReactDOMRe.domElementToObj
                                       )##value;