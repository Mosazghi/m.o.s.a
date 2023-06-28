import { Injectable } from '@nestjs/common';
import { InjectModel } from '@nestjs/mongoose';
import { Model } from 'mongoose';
import { CreateUserDto } from './dto/create-user.dto';
import { User } from './schema/user.schema';

export type Users = any;

@Injectable()
export class UserService {
  constructor(
    @InjectModel(User.name) private readonly userModel: Model<User>,
  ) {}

  async createUser(createUserDto: CreateUserDto) {
    if (!(await this.userModel.findOne({ username: createUserDto.username }))) {
      const newUser = new this.userModel(createUserDto);
      console.log('NEW USER, POST:', newUser);
      return newUser.save();
    } else return null;
  }

  findAll() {
    return `This action returns all user`;
  }

  async findOne(username) {
    return await this.userModel.findOne({ username: username });
  }

  async findById(id) {
    return await this.userModel.findById(id);
  }

  remove(id: number) {
    return `This action removes a #${id} user`;
  }
}
