import React from "react";

function Ip() {
    return (
        <div>
            <form className="form-style" m>
                <label> Enter IP Address: </label>
                <input type="text" id="ip" placeholder="Enter IP here"></input><br />   
            </form>
            <div className="submit-style"><input type="submit"></input></div>
        </div>
    );
}

export default Ip;