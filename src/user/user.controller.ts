import {
  Body,
  Controller,
  Get,
  HttpStatus,
  Next,
  Param,
  Post,
  Redirect,
  Req,
  Request,
  Res,
  Response,
  UseFilters,
  UseGuards,
} from '@nestjs/common';
import { LocalAuthGuard } from 'src/auth/local-auth.guard';
import { ViewAuthFilter } from 'src/auth/redirect-to-login';
import { CreateUserDto } from './dto/create-user.dto';
import { UserService } from './user.service';

@Controller('user')
export class UserController {
  constructor(private readonly userService: UserService) {}

  @Post('/register')
  async createUser(@Res() res, @Body() createUserDto: CreateUserDto) {
    const newUser = this.userService.createUser(createUserDto);
    console.log('new user:', newUser);
    if ((await newUser) !== null) {
      res.redirect('/');
    } else {
      res.status(HttpStatus.BAD_REQUEST).send('Bruker finnes allerde!');
    }
  }

  @UseGuards(LocalAuthGuard)
  @Post('/login')
  async login(@Request() req, @Response() res, @Next() next) {
    console.log('LOGGED IN', req.isAuthenticated());
    if (req) {
      res.redirect('/dashboard');
    } else res.send('/');
  }

  @Get(':id')
  findOne(@Param('id') id: string) {
    return this.userService.findOne(+id);
  }
}
