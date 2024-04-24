import axios from 'axios';
import React from 'react';
import { Link } from 'react-router-dom';

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


const Users = () => {
    const [users, setUsers] = React.useState < Array < User >> ([])
    const [errorFlag, setErrorFlag] = React.useState(false)
    const [errorMessage, setErrorMessage] = React.useState("")
    React.useEffect(() => {
        getUsers()
    }, [])
    const getUsers = () => {
        axios.get('http://localhost:3000/api/users')
            .then((response) => {
                setErrorFlag(false)
                setErrorMessage("")
                setUsers(response.data)
            }, (error) => {
                setErrorFlag(true)
                setErrorMessage(error.toString())
        })
    }

    const deleteUser = (user: User) => {
        axios.delete('http://localhost:3000/api/users/'+user.user_id)
            .then((response) => {
                setUsers(users.filter((item: User) => item.user_id !== user.user_id))
            }, (error) => {
                setErrorFlag(true)
                setErrorMessage(error.toString())
            })
    }

    const editUser = async (user: User) => {
        const element = document.getElementById('closeButton') as HTMLElement;
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

    const list_of_users = () => {
        return users.map((item: User) =>
            <tr key={item.user_id}>
                <th scope="row">{item.user_id}</th>
                <td>{item.username}</td>
                <td><Link to={"/users/" + item.user_id}>Go to
                    user</Link></td>
                <td>
                    <button type="button"  className="btn btn-primary" data-toggle="modal" data-target={"#deleteUserModal" + item.user_id}>
                        Delete
                    </button>
                    <button type="button" data-toggle='modal' data-target={"#editUserModal" + item.user_id}>Edit</button>
                </td>
            </tr>
        )
    }
    const deleteModals = () => {
        return users.map((item: User) =>
            <div className="modal fade" id={"deleteUserModal" + item.user_id} tabIndex={-1} role="dialog"
                aria-labelledby="deleteUserModalLabel" aria-hidden="true" key={"del"+item.user_id}>
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
                                onClick={() => deleteUser(item)}>
                                    Delete User
                                </button>
                            </div>
                        </div>
                    </div>
            </div>
        )
    }

    const onChange = (user: User, username: string) => {
        const new_array = users.map((item: User) => {
            if (item.user_id === user.user_id) {
                return {
                    ...item,
                    username: username
                }
            } else {
                return item
            }
        })
        setUsers(new_array)
    }

    const editModals = () => {
        return users.map((user: User) =>
            <div className="modal fade" id={"editUserModal" + user.user_id} tabIndex={-1} role="dialog"
            aria-labelledby="editUserModalLabel" aria-hidden="true" key={"edit"+user.user_id}>
                <div className="modal-dialog" role="document">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id="editUserModalLabel">Edit User</h5>
                            <button type="button" className="close" data-dismiss="modal" aria-label="Close" id='closeButton'>
                                <span aria-hidden="true">&times;</span>
                            </button>
                        </div>
                        <div className="modal-body">
                            <form onSubmit={(e) => {e.preventDefault(); editUser(user)}}>
                                <div className="form-group">
                                    <label htmlFor="username">Username</label>
                                    <input type="text" className="form-control" id="username" name="username"
                                    value={user.username} onChange={(e) => onChange(user, e.target.value)} />
                                </div>
                                <button type="submit" className="btn btn-primary">Edit User</button>
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        )
    }

    const adduser = () => {
        const element = document.getElementById('closeButton') as HTMLElement;
        simulateMouseClick(element);
        const username = (document.getElementById('addUsername') as HTMLInputElement).value;
        axios.post('http://localhost:3000/api/users', {
            username: username
        })
            .then((response) => {
                const new_user = {username: username, user_id: response.data} as User
                setUsers([...users, new_user])
            }, (error) => {
                setErrorFlag(true)
                setErrorMessage(error.toString())
            })
    }

    const addUserModal = () => {
        return (
            <div className="modal fade" id="addUserModal" tabIndex={-1} role="dialog"
            aria-labelledby="addUserModalLabel" aria-hidden="true">
                <div className="modal-dialog" role="document">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id="addUserModalLabel">Add User</h5>
                            <button type="button" className="close" data-dismiss="modal" aria-label="Close">
                                <span aria-hidden="true">&times;</span>
                            </button>
                        </div>
                        <div className="modal-body">
                            <form onSubmit={(e) => adduser} >
                                <div className="form-group">
                                    <label htmlFor="username">Username</label>
                                    <input type="text" className="form-control" id="addUsername" name="username" />
                                </div>
                                <button type="submit" className="btn btn-primary">Add User</button>
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        )
    }

    if (errorFlag) {
        return (
            <div>
                <h1>Users</h1>
                <div style={{color: 'red'}}>{errorMessage}</div>
            </div>
        )
    } else {
        return (
            <div>
                <h1>Users</h1>
                <table className='table'>
                    <thead>
                        <tr>
                            <th scope='col'>#</th>
                            <th scope='col'>Username</th>
                            <th scope='col'>link</th>
                            <th scope='col'>actions</th>
                        </tr>
                    </thead>
                    <tbody>
                        {list_of_users()}
                    </tbody>
                </table>
                {deleteModals()}
                {editModals()}
                <button type="button" className="btn btn-primary" data-toggle="modal" data-target="#addUserModal">
                    Add User
                </button>
                {addUserModal()}
            </div>
        )
    }
}

export default Users;