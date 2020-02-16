  open Aim;

  let div = (~children, ()) => html("div", [], children);
  let button = (~id, ~onClick, ~children, ()) =>
    html("button", [attr("id", id), event("click", onClick)], children);

  let span = (~id="", ~children, ()) =>
    html("span", [attr("id", id)], children);
    