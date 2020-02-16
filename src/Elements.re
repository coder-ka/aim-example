open Aim;

let div = (~children, ()) => html("div", [], children);
let button = (~onClick, ~children, ()) =>
  html("button", [event("click", onClick)], children);

let span = (~children, ()) => html("span", [], children);
