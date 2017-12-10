let valueFromEvent = (evt) : string => (
                                         evt
                                         |> ReactEventRe.Form.target
                                         |> ReactDOMRe.domElementToObj
                                       )##value;

type result('o, 'e) =
  | Ok('o)
  | Err('e);