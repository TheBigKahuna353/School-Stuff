import { Dialog, DialogTitle, DialogContent, DialogContentText, DialogActions, Button, TextField, Paper, Table, TableBody, TableCell, TableContainer, TableHead, TableRow, Stack, Alert, AlertTitle, Snackbar } from '@mui/material';
import axios from 'axios';
import React from 'react';
import { Link } from 'react-router-dom';
import DeleteIcon from "@mui/icons-material/Delete";
import EditIcon from "@mui/icons-material/Edit";
import CSS from 'csstype';


const card: CSS.Properties = {
    padding: "10px",
    margin: "auto",
    maxWidth: "800px",

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

    const deleteUser = () => {
        const user = dialogUser
        axios.delete('http://localhost:3000/api/users/'+user.user_id)
            .then((response) => {
                setUsers(users.filter((item: User) => item.user_id !== user.user_id))
                setSnackMessage("User deleted successfully")
                setSnackOpen(true)
            }, (error) => {
                setErrorFlag(true)
                setErrorMessage(error.toString())
            })
    }

    const editUser = () => {
        const user = dialogUser
        axios.put('http://localhost:3000/api/users/'+user.user_id, {
            username: user.username
        })
            .then((response) => {
                const new_user = {username: user.username, user_id: user.user_id} as User
                setUsers(users.map((item: User) => item.user_id === user.user_id ? new_user : item))
                setSnackMessage("Username changed successfully")
                setSnackOpen(true)
            }, (error) => {
                setErrorFlag(true)
                setErrorMessage(error.toString())
            })
    }

    const updateUsernameEditState = (e: React.ChangeEvent<HTMLInputElement>) => {
        setDialogUser({username: e.target.value, user_id: dialogUser.user_id})
    }


    const list_of_users = () => {
        return users.map((item: User) =>
            <TableRow hover
                tabIndex={-1}
                key={item.user_id}>
                <TableCell>
                    {item.user_id}
                </TableCell>
                <TableCell align="right">{item.username}</TableCell>
                <TableCell align="right"><Link
                    to={"/users/" + item.user_id}>Go to user</Link></TableCell>
                <TableCell align="right">
                    <Button variant="outlined" endIcon={<EditIcon />} onClick={() => { handleEditDialogOpen(item) }}>
                        Edit
                    </Button>
                    <Button variant="outlined" endIcon={<DeleteIcon />} onClick={() => { handleDeleteDialogOpen(item)}}>
                        Delete
                    </Button>
                </TableCell>
            </TableRow>
        )
    }

    interface HeadCell {
        id: string;
        label: string;
        numeric: boolean;
    }
    const headCells: readonly HeadCell[] = [
        { id: 'ID', label: 'id', numeric: true },
        { id: 'username', label: 'Username', numeric: false },
        { id: 'link', label: 'Link', numeric: false },
        { id: 'actions', label: 'Actions', numeric: false }
    ];

    // delete dialog
    const [openDeleteDialog, setOpenDeleteDialog] = React.useState(false)
    const [dialogUser, setDialogUser] = React.useState<User>({ username: "", user_id: -1 })
    const handleDeleteDialogOpen = (user: User) => {
        setDialogUser(user)
        setOpenDeleteDialog(true);
    };
    const handleDeleteDialogClose = () => {
        setDialogUser({ username: "", user_id: -1 })
        setOpenDeleteDialog(false);
    };

    // edit dialog
    const [openEditDialog, setOpenEditDialog] = React.useState(false)
    const handleEditDialogOpen = (user: User) => {
        setDialogUser(user)
        setOpenEditDialog(true);
    };
    const handleEditDialogClose = () => {
        setDialogUser({ username: "", user_id: -1 })
        setOpenEditDialog(false);
    };


    // snack bar
    const [snackOpen, setSnackOpen] = React.useState(false)
    const [snackMessage, setSnackMessage] = React.useState("")
    const handleSnackClose = (event?: React.SyntheticEvent | Event, reason?: string) => {
        if (reason === 'clickaway') {
            return;
        }
        setSnackOpen(false);
    };

    const [addUserUsername, setAddUserUsername] = React.useState("")

    const addUser = () => {
        
        const username = addUserUsername
        axios.post('http://localhost:3000/api/users', {
            username: username
        })
            .then((response) => {
                const new_user = {username: username, user_id: response.data.user_id} as User
                setUsers([...users, new_user])
                setAddUserUsername("")
                setSnackMessage("User added successfully")
                setSnackOpen(true)
            }, (error) => {
                setErrorFlag(true)
                setErrorMessage(error.toString())
            })
    }

    

    return (
        <div>
            <Paper elevation={3} style={card}>
                <h1>Users</h1>
                <TableContainer component={Paper}>
                    <Table>
                        <TableHead>
                            <TableRow>
                                {headCells.map((headCell) => (
                                    <TableCell
                                        key={headCell.id}
                                        align={headCell.numeric ? 'right' :
                                            'left'}
                                        padding={'normal'}>
                                        {headCell.label}
                                    </TableCell>
                                ))}
                            </TableRow>
                        </TableHead>
                        <TableBody>
                            {list_of_users()}
                        </TableBody>
                    </Table>
                </TableContainer>
            </Paper>
            <Paper elevation={3} style={card}>
                <h1>Add a new user</h1>
                <Stack direction="row" spacing={2} justifyContent="center">
                    <TextField id="outlined-basic" label="Username" variant="outlined" value={addUserUsername}
                    onChange={(event) => setAddUserUsername(event.target.value)} />
                    <Button variant="outlined" onClick={() => { addUser() }}>
                        Submit
                    </Button>
                </Stack>
            </Paper>
            <Dialog
                open={openDeleteDialog}
                onClose={handleDeleteDialogClose}
                aria-labelledby="alert-dialog-title"
                aria-describedby="alert-dialog-description">
                <DialogTitle id="alert-dialog-title">
                    {"Delete User?"}
                </DialogTitle>
                <DialogContent>
                    <DialogContentText id="alert-dialog-description">
                        Are you sure you want to delete this user?
                    </DialogContentText>
                </DialogContent>
                <DialogActions>
                    <Button onClick={handleDeleteDialogClose}>Cancel</Button>
                    <Button variant="outlined" color="error" onClick={() => {
                        deleteUser()
                        handleDeleteDialogClose()
                    }} autoFocus>
                        Delete
                    </Button>
                </DialogActions>
            </Dialog>
            <Dialog
                open={openEditDialog}
                onClose={handleEditDialogClose}
                aria-labelledby="alert-dialog-title"
                aria-describedby="alert-dialog-description">
                <DialogTitle id="alert-dialog-title">
                    {"Edit User"}
                </DialogTitle>
                <DialogContent>
                <TextField id="outlined-basic" label="Username" variant="outlined"
                    value={dialogUser.username} onChange={updateUsernameEditState} />
                </DialogContent>
                <DialogActions>
                    <Button onClick={handleEditDialogClose}>Cancel</Button>
                    <Button variant="outlined" color="primary" onClick={() => {
                        editUser()
                        handleEditDialogClose()
                    }} autoFocus>
                        Save Changes
                    </Button>
                </DialogActions>
            </Dialog>

            {errorFlag &&
                <Alert severity="error">
                    <AlertTitle>Error</AlertTitle>
                    {errorMessage}
                </Alert>}

            <Snackbar
                autoHideDuration={6000}
                open={snackOpen}
                onClose={handleSnackClose}
                key={snackMessage}
                >
                <Alert onClose={handleSnackClose} severity="success" sx={{
                width: '100%'
                }}>
                {snackMessage}
                </Alert>
            </Snackbar>


        </div>
    )
}

export default Users;