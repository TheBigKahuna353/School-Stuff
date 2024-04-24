import axios from "axios";
import React from "react";
import { useParams, useNavigate, Link } from "react-router-dom";

const mouseClickEvents = ['mousedown', 'click', 'mouseup'];
function simulateMouseClick(element: HTMLElement){
  mouseClickEvents.forEach(mouseEventType =>
    element.dispatchEvent(
      new MouseEvent(mouseEventType, {
          view: window,
          bubbles: true,
          cancelable: true,
          buttons: 1
      })
    )
  );
}

const User = () => {

    const {id} = useParams();
    const navigate = useNavigate();
    const [user, setUser] = React.useState<User>({user_id:0, username:""})
    const [errorFlag, setErrorFlag] = React.useState(false)
    const [errorMessage, setErrorMessage] = React.useState("")
    React.useEffect(() => {
        const getUser = () => {
            axios.get('http://localhost:3000/api/users/'+id)
                .then((response) => {
                    setErrorFlag(false)
                    setErrorMessage("")
                    setUser(response.data)
                }, (error) => {
                    setErrorFlag(true)
                    setErrorMessage(error.toString())
                })
        }
        getUser()
    }, [id])

    const deleteUser = (user: User) => {
        axios.delete('http://localhost:3000/api/users/'+user.user_id)
            .then((response) => {
                navigate('/users')
            }, (error) => {
                setErrorFlag(true)
                setErrorMessage(error.toString())
            })
    }

    const editUser = async (e: React.FormEvent<HTMLFormElement>) => {
        e.preventDefault()
        let element = document.getElementById('closeButton') as HTMLElement;
        simulateMouseClick(element);
        console.log("editing user")
        axios.put('http://localhost:3000/api/users/'+user.user_id, user)
            .then((response) => {
                console.log(response)
            }, (error) => {
                setErrorFlag(true)
                setErrorMessage(error.toString())
            })
    }

    if (errorFlag) {
        return (
            <div>
                <h1>User</h1>
                <div style={{ color: "red" }}>
                    {errorMessage}
                </div>
                <Link to={"/users"}>Back to users</Link>
            </div>
        )
    } else {
        return (
        <div>
            <h1>User</h1>
            {user.user_id}: {user.username}
            <Link to={"/users"}>Back to users</Link>
            <button type="button" className="btn btn-secondary" data-toggle="modal" data-target="#editUserModal">
                Edit
            </button>
            <button type="button" className="btn btn-primary" data-toggle="modal" data-target="#deleteUserModal">
                Delete
            </button>
            <div className="modal fade" id="deleteUserModal" tabIndex={-1} role="dialog"
            aria-labelledby="deleteUserModalLabel" aria-hidden="true">
                <div className="modal-dialog" role="document">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id="deleteUserModalLabel">Delete User</h5>
                            <button type="button" className="close" data-dismiss="modal" aria-label="Close">
                                <span aria-hidden="true">&times;</span>
                            </button>
                        </div>
                        <div className="modal-body">
                            Are you sure that you want to delete this user?
                        </div>
                        <div className="modal-footer">
                            <button type="button" className="btn btn-secondary" data-dismiss="modal">
                                Close
                            </button>
                            <button type="button" className="btn btn-primary" data-dismiss="modal"
                            onClick={() => deleteUser(user)}>
                                Delete User
                            </button>
                        </div>
                    </div>
                </div>
            </div>
            <div className="modal fade" id="editUserModal" tabIndex={-1} role="dialog"
            aria-labelledby="editUserModalLabel" aria-hidden="true">
                <div className="modal-dialog" role="document">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id="editUserModalLabel">Edit User</h5>
                            <button type="button" className="close" data-dismiss="modal" aria-label="Close" id='closeButton'>
                                <span aria-hidden="true">&times;</span>
                            </button>
                        </div>
                        <div className="modal-body">
                            <form onSubmit={editUser}>
                                <div className="form-group">
                                    <label htmlFor="username">Username</label>
                                    <input type="text" className="form-control" id="username" name="username"
                                    value={user.username} onChange={(e) => setUser({...user, username: e.target.value})} />
                                </div>
                                <button type="submit" className="btn btn-primary">Edit User</button>
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        )
    }
}

export default User;